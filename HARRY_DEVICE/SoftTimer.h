#ifndef SOFTTIMER_H // Header guard
#define SOFTTIMER_H

#include "Task.h"
#include "Types.h"

class SoftTimer : public Task
{
private:
    int status;
public:
    // Constructor
    SoftTimer();
    // Destructor
    ~SoftTimer();

    // Methods
    void set_status(int value);
    int get_status(void);

    void init(void) override;
    void run_function(void) override;
    void cleanUp(void) override;

};

#endif // DATALOGGER_H