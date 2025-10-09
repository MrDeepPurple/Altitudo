#ifndef SETTINGS_H
#define SETTINGS_H

#include <Preferences.h>
#include <math.h>
#include <MS5611.h>

#define MAVG_SIZE 10 // 100ms avg

enum HeightUnit { METERS, FEET };
enum TemperatureUnit { CELSIUS, FAHRENHEIT };
enum PressureUnit { HPA, INHG };

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
    public:
        double QFE = 1013.25; // QFE in hPa
        double QNH = 1013.25; // QNH in hPa
        HeightUnit heightUnit = METERS;
        TemperatureUnit temperatureUnit = CELSIUS;
        PressureUnit pressureUnit = HPA;
        void load()
        {
            storage.begin(storage_name, true);
            QFE = storage.getDouble(storage_qfe, 1013.25);
            QNH = storage.getDouble(storage_qnh, 1013.25);
            heightUnit = static_cast<HeightUnit>(storage.getUChar(storage_hu, static_cast<uint8_t>(METERS)));
            temperatureUnit = static_cast<TemperatureUnit>(storage.getUChar(storage_tu, static_cast<uint8_t>(CELSIUS)));
            pressureUnit = static_cast<PressureUnit>(storage.getUChar(storage_pu, static_cast<uint8_t>(FAHRENHEIT)));
            storage.end();
        }
        void save()
        {
            storage.begin(storage_name, false);
            storage.putDouble(storage_qfe, QFE);
            storage.putDouble(storage_qnh, QNH);
            storage.putUChar(storage_hu, static_cast<uint8_t>(heightUnit));
            storage.putUChar(storage_tu, static_cast<uint8_t>(temperatureUnit));
            storage.putUChar(storage_pu, static_cast<uint8_t>(pressureUnit));
            storage.end();
        }
};

/* data class containing altimeter reads and calculations */
class AltimeterData
{
    public:
        float altitude = 0.0;     // Altitude above sea level
        float height = 0.0;       // Height above ground level
        float temperature = 23.5;  // Temperature in Kelvin
        float pressure = 1013.25; // Pressure in hPa
};

/* altimeter sensor wrapper */
class Altimeter
{
    public:
        void begin() {
            /* initialize and load from eeprom */
            settings.load();

            /* initialize moving average buffer */
            for (uint8_t i = 0; i < MAVG_SIZE; i++)
            {
                /* initialize moving average to the default values */
                mavg_buff_temp[mavg_idx] = data.temperature;
                mavg_buff_pres[mavg_idx] = data.pressure;
            }
            
            /* initialize I2C connection to ms5611 baro */
            while(!ms5611.begin())
            {
                delay(500);
            }
            ms5611.reset(1); //<-- set math mode
            ms5611.setOversampling(OSR_HIGH);
        }

        AltimeterSettings &getSettings() {
            return settings;
        }

        AltimeterData &getData() {
            return data;
        }

        void read() {
            ms5611.read();
           // Read temperature and pressure from the sensor
            double temperature = ms5611.getTemperature() + 273.15; // Convert to Kelvin
            double pressure = ms5611.getPressure();
            update(temperature, pressure);

        }
    private:
        MS5611 ms5611;
        AltimeterData data;
        AltimeterSettings settings;
        const double P_filter = 0.1;
        const double T_filter = 0.3;
        const double R = 8.31432;    // Universal gas constant in N·m/(mol·K)
        const double g = 9.80665;    // Acceleration due to gravity in m/s²
        const double M = 0.0289644;  // Molar mass of Earth's air in kg/mol
        const double L = 0.0065;     // Temperature lapse rate in K/m
        const double T0 = 288.15;    // Standard temperature at sea level in K
        double precise_altitude_formula(double pressure, double p0, double T) {
            return (T0 / L) * (1 - pow(pressure / p0, (R * L) / (g * M)));
        }
        const double C0 = 44330.0; // Constant for altitude calculation in meters
        const double C1 = 0.1903; // Exponent for altitude calculation
        double simple_altitude_formula(double pressure, double p0) {
            return C0 * (1.0 - pow(pressure / p0, C1));
        }
        double mavg_buff_temp[MAVG_SIZE];
        double mavg_buff_pres[MAVG_SIZE];
        uint8_t mavg_idx = 0;

        void update(float temp, float pres) {
            
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

            data.temperature = avg_tmp;
            data.pressure = avg_prs;
            // Calculate altitude using the barometric formula
            #ifdef USE_PRECISE_FORMULA
            data.altitude = precise_altitude_formula(pres, settings.QNH, temp);
            double ground_altitude = precise_altitude_formula(settings.QFE, settings.QNH, temp);
            #else
            data.altitude = P_filter * simple_altitude_formula(pres, settings.QNH) + (1 - P_filter) * data.altitude;
            double ground_altitude = simple_altitude_formula(settings.QFE, settings.QNH);
            #endif
            // Height calculation can be added if ground level pressure is known
            data.height = data.altitude - ground_altitude;
        }
};

#endif //SETTINGS_H