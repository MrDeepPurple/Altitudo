#ifndef SETTINGS_H
#define SETTINGS_H

#include <Preferences.h>
#include <math.h>
#include "utils/hwconfig.h"
#if BAROMETER_TYPE == BT_BMP585
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP5xx.h"
#elif BAROMETER_TYPE == BT_MS5611
#include <MS5611.h>
#else
#error "No valid barometer type selected"
#endif

#define MAVG_SIZE 10 // 100ms avg
#define MAX_SKIPPABLE_READS 5 // if more reads are skipped, consider the sensor failed

#define DEFAULT_TEMPERATURE_K 288.15
#define SEA_LEVEL_PRESSURE_HPA 1013.25

enum HeightUnit { METERS, FEET };
enum TemperatureUnit { CELSIUS, FAHRENHEIT };
enum PressureUnit { HPA, INHG };
enum UIMode { STANDARD, COMPACT };

/* settings related to altimeter display and calibration */
class AltimeterSettings
{
    private:
        Preferences storage;
        const char* storage_name = "settings";
        const char* storage_qfe = "QFE";
        const char* storage_qnh = "QNH";
        const char* storage_hu = "heightUnit";
        const char* storage_tu = "tempUnit";
        const char* storage_pu = "pressUnit";
        const char* storage_ui = "uiMode";
    public:
        double QFE = SEA_LEVEL_PRESSURE_HPA; // QFE in hPa
        double QNH = SEA_LEVEL_PRESSURE_HPA; // QNH in hPa
        HeightUnit heightUnit = METERS;
        TemperatureUnit temperatureUnit = CELSIUS;
        PressureUnit pressureUnit = HPA;
        UIMode uiMode = STANDARD;
        bool load()
        {
            bool ret = false;
            if (storage.begin(storage_name, true))
            {
                QFE = storage.getDouble(storage_qfe, SEA_LEVEL_PRESSURE_HPA);
                QNH = storage.getDouble(storage_qnh, SEA_LEVEL_PRESSURE_HPA);
                heightUnit = static_cast<HeightUnit>(storage.getUChar(storage_hu, static_cast<uint8_t>(METERS)));
                temperatureUnit = static_cast<TemperatureUnit>(storage.getUChar(storage_tu, static_cast<uint8_t>(CELSIUS)));
                pressureUnit = static_cast<PressureUnit>(storage.getUChar(storage_pu, static_cast<uint8_t>(FAHRENHEIT)));
                uiMode = static_cast<UIMode>(storage.getUChar(storage_ui, static_cast<uint8_t>(COMPACT)));
                storage.end();
            }
            else
            {
                ret = false;
            }
            return ret;
        }
        bool save()
        {
            bool ret = true;
            if(storage.begin(storage_name, false))
            {
                storage.putDouble(storage_qfe, QFE);
                storage.putDouble(storage_qnh, QNH);
                storage.putUChar(storage_hu, static_cast<uint8_t>(heightUnit));
                storage.putUChar(storage_tu, static_cast<uint8_t>(temperatureUnit));
                storage.putUChar(storage_pu, static_cast<uint8_t>(pressureUnit));
                storage.putUChar(storage_ui, static_cast<uint8_t>(uiMode));
                storage.end();
            }
            else
            {
                ret = false;
            }
            return ret;
        }
};

/* data class containing altimeter reads and calculations */
class AltimeterData
{
    public:
        float altitude = 0.0;     // Altitude above sea level
        float height = 0.0;       // Height above ground level
        float temperature = DEFAULT_TEMPERATURE_K;  // Temperature in Kelvin
        float pressure = SEA_LEVEL_PRESSURE_HPA; // Pressure in hPa
};

/* altimeter sensor wrapper */
class Altimeter
{
    public:
        bool begin() {
            bool ret = true;
            /* initialize and load from eeprom */
            if (settings.load())
            {
                /* initialize moving average buffer */
                for (uint8_t i = 0; i < MAVG_SIZE; i++)
                {
                    /* initialize moving average to the default values */
                    mavg_buff_temp[mavg_idx] = data.temperature;
                    mavg_buff_pres[mavg_idx] = data.pressure;
                }
                /* initialize I2C connection to BAROMETER */
                if(baro.begin())
                {
                #if BAROMETER_TYPE == BT_MS5611
                    baro.reset(MATH_MODE); //<-- set math mode to 1, otherwise temperature calculation is off by factor 2
                    baro.setOversampling(OSR_HIGH);
                #elif BAROMETER_TYPE == BT_MS5611
                    baro.setTemperatureOversampling(BMP5XX_OVERSAMPLING_2X);
                    baro.setPressureOversampling(BMP5XX_OVERSAMPLING_16X);
                    baro.setIIRFilterCoeff(BMP5XX_IIR_FILTER_COEFF_3);
                    baro.setOutputDataRate(BMP5XX_ODR_100_2_HZ);
                    baro.setPowerMode(BMP5XX_POWERMODE_NORMAL);
                    baro.enablePressure(true);
                    baro.configureInterrupt(BMP5XX_INTERRUPT_LATCHED, BMP5XX_INTERRUPT_ACTIVE_HIGH, BMP5XX_INTERRUPT_PUSH_PULL, BMP5XX_INTERRUPT_DATA_READY, true);
                #endif
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = false;
            }
            return ret;
        }

        AltimeterSettings &getSettings() {
            return settings;
        }

        AltimeterData &getData() {
            return data;
        }

        bool read() {
            bool ret = true;
            #if BAROMETER_TYPE == BT_BMP585
            if(baro.dataReady())
            {
                read_skipped = 0;
                if (!baro.perofmReading())
                {
                    ret = false;
                    temperature = NAN;
                    pressure = NAN;
                }
                else
                {
                    // get temperature and pressure from the sensor.
                    // Temperature is in C, so convert to K before passing it
                    // to the update function.
                    update((baro.temperature + 273.15), baro.pressure);
                }
            }
            else
            {
                read_skipped++:
            }

            if (read_skipped > MAX_SKIPPABLE_READS)
            {
                ret = false;
            }
            #elif BAROMETER_TYPE == BT_MS5611
            if(baro.read() != MS5611_READ_OK)
            {
                ret = false;
            }
            else
            {
                // get temperature and pressure from the sensor.
                // Temperature is in C, so convert to K before passing it
                // to the update function.
                update((baro.getTemperature() + 273.15), baro.getPressure());
            }
            #endif
            return ret;
        }
    private:
        #if BAROMETER_TYPE == BT_MS5611
        MS5611 baro;
        #elif BAROMETER_TYPE == BT_BMP585
        Adafruit_BMP585 baro;
        #endif
        AltimeterData data;
        AltimeterSettings settings;
        int read_skipped = 0;
        const double P_filter = 0.1;
        const double T_filter = 0.3;
        #ifdef USE_PRECISE_FORMULA
        const double R = 8.31432;    // Universal gas constant in N·m/(mol·K)
        const double g = 9.80665;    // Acceleration due to gravity in m/s²
        const double M = 0.0289644;  // Molar mass of Earth's air in kg/mol
        const double L = 0.0065;     // Temperature lapse rate in K/m
        const double T0 = 288.15;    // Standard temperature at sea level in K
        double altitude_formula(double pressure, double p0, double T) {
            return (T0 / L) * (1 - pow(pressure / p0, (R * L) / (g * M)));
        }
        #else
        const double C0 = 44330.0; // Constant for altitude calculation in meters
        const double C1 = 0.1903; // Exponent for altitude calculation
        double altitude_formula(double pressure, double p0) {
            return C0 * (1.0 - pow(pressure / p0, C1));
        }
        #endif
        double mavg_buff_temp[MAVG_SIZE];
        double mavg_buff_pres[MAVG_SIZE];
        uint8_t mavg_idx = 0;

        void update(float temp, float pres) {
            #ifdef USE_ROLLING_AVG
            mavg_buff_temp[mavg_idx] = temp;
            mavg_buff_pres[mavg_idx] = pres;
            mavg_idx = (mavg_idx + 1) % MAVG_SIZE;

            double avg_tmp = 0;
            double avg_prs = 0;
            for (uint8_t i = 0; i < MAVG_SIZE; i++)
            {
                avg_tmp += mavg_buff_temp[i];
                avg_prs += mavg_buff_pres[i];
            }
            avg_tmp /= MAVG_SIZE;
            avg_prs /= MAVG_SIZE;
            #else
            double avg_tmp = T_filter * temp + (1 - T_filter) * data.temperature;
            double avg_prs = P_filter * pres + (1 - P_filter) * data.pressure;
            #endif

            data.temperature = avg_tmp;
            data.pressure = avg_prs;
            // Calculate altitude using the barometric formula
            #ifdef USE_PRECISE_FORMULA
            data.altitude = altitude_formula(pres, settings.QNH, temp);
            double ground_altitude = altitude_formula(settings.QFE, settings.QNH, temp);
            #else
            data.altitude = P_filter * altitude_formula(pres, settings.QNH) + (1 - P_filter) * data.altitude;
            double ground_altitude = altitude_formula(settings.QFE, settings.QNH);
            #endif
            // Height calculation can be added if ground level pressure is known
            data.height = data.altitude - ground_altitude;
        }
};

#endif //SETTINGS_H