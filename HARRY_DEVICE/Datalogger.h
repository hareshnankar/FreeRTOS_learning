// Declare the event group

#ifndef DATALOGGER_H // Header guard
#define DATALOGGER_H

#include "Task.h"
#include "Types.h"

// Preprocessor directives

#define QUOTECHAR '\"'
#define C_TIMESTAMP                     "Timestamp"
#define C_SYSTEMDATE                    "SystemDate="
#define C_SYSTEMTIME                    "SystemTime="
#define C_STARTTIME                     "StartTime="
#define C_ENDTIME                       "EndTime="
#define C_INTERVAL                      "LogInterval="
#define C_DURATION                      "LogDuration="
#define C_DATAPNO                       "NoOfDataPoint="
#define C_MESURNO                       "NoOfMesurment="
#define C_LOGSTATUS						"LogStatus="

#define C_MOISTURM2SENS                 "MH"
#define C_DEWPOINT						"DP"
#define C_MOISTURMISP2SENS              "FH"
#define C_PRESSURE			            "Pressure"
#define C_SENSTEMP			            "SensorTmp"
#define C_OXYPER			            "OxygenPer"
#define C_BORADTMP			            "OnBoardTmp"


#define C_TRIGGER                       "LogTrigger="
#define C_PRIMARY                       "Primary"
#define C_SECONDARY                     "Secondary"
#define C_FUNCTION                      "Function="
#define C_CH1_PRI_FUNCTION              "CH1 Primary Function="
#define C_CH1_SEC_FUNCTION              "CH1 Secondary Function="
#define C_CH2_PRI_FUNCTION              "CH2 Primary Function="
#define C_CH2_SEC_FUNCTION              "CH2 Secondary Function="
#define C_CH3_PRI_FUNCTION              "CH3 Primary Function="
#define C_NONE                          "None"
#define C_ANALYSIS                      "Analysis="
#define C_NEGFS                         "NegFS="
#define C_POSFS                         "PosFS="
#define C_UNIT                          "Unit="
#define C_SENSORTYPE                    "SensorType="
#define C_TARE                          "Tare="
#define C_SCALING                       "Scaling="
#define C_USER                          "User"
#define C_DELIMITER                     "|"
#define C_CH1                           "CH1"
#define C_CH2                           "CH2"
#define C_PFS                           "PFS"       // positive full scale
#define C_HARTPVUNIT                    "PVUnit"
#define C_KEYPRESS                      "Keypress"
#define C_PERIODIC                      "Periodic"
#define C_ENABLED                       "Enabled"
#define C_DISABLED                      "Disabled"
#define C_ZERO                          "0"         // for backward compatibility
#define C_ONE                           "1"         // for backward compatibility

#define EV_FLAG_HEADER_INFO 0x00000001u

#define EV_FLAG_LOG_DATA 0x00000002u

//extern EventGroupHandle_t myEventFlagsDataLogger;

//typedef enum
//{
//    E_DATALOG_ERROR_NONE,
//    E_DATALOG_ERROR_MODE,
//    E_DATALOG_ERROR_PATH,
//    E_DATALOG_ERROR_FILENAME,
//    E_DATALOG_ERROR_WRITE,
//    E_DATALOG_ERROR_TIMER,
//    E_DATALOG_ERROR_SPACE,
//    E_DATALOG_ERROR_FILESIZE_ERROR,
//    E_DATALOG_ERROR_FILESIZE_LARGE,
//    E_DATALOG_ERROR_EXCESSIVE_SAMPLE_RATE
//} eDataLogError_t;

class Datalogger : public Task
{
private:
    int status;
public:
    // Constructor
    Datalogger();
    // Destructor
    ~Datalogger();

    // Methods
    void set_status(int value);
    int get_status(void);

    void init(void) override;
    void run_function(void) override;
    void cleanUp(void) override;

    void setHeaderInfo(void);
    void headerPrepareInstrumentInfo(char* text);
    void headerPrepareColumnHeader(char* text);
    void GetDummyTime(sTime_t* time1); // For simulation purpose only
    void prepareDummyDataLine(char* text);
    void startSession(void);
};

#endif // DATALOGGER_H
