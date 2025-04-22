#ifndef HMIASKEYBOARD_H // Header guard
#define HMIASKEYBOARD_H

#include "Task.h"
#include "Types.h"

class HmiAsKeyboard : public Task
{
private:
    int status;
public:
    // Constructor
    HmiAsKeyboard();
    // Destructor
    ~HmiAsKeyboard();

    // Methods
    void set_status(int value);
    int get_status(void);

    void init(void) override;
    void run_function(void) override;
    void cleanUp(void) override;

}; 

#endif // HMIASKEYBOARD_H
