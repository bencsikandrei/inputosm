#include <inputosm/inputosm_c.h>

#include "time.h"
#include "stdio.h"

const char* lvl_to_str(const inputosm_log_level_t lvl)
{
    switch (lvl)
    {
        case INPUTOSM_LOG_LEVEL_TRACE:
            return "TRC";
        case INPUTOSM_LOG_LEVEL_INFO:
            return "INF";
        case INPUTOSM_LOG_LEVEL_ERROR:
            return "ERR";
        default:
            break;
    }
    return "NON";
}

static void phony_log_callback(inputosm_log_level_t level, const char* message)
{
    const time_t t = time(NULL);
    char time_buf[100];
    size_t rc = strftime(time_buf, sizeof(time_buf), "%D %T", gmtime(&t));
    snprintf(time_buf + rc, sizeof(time_buf) - rc, ".%06ld UTC", t / 1000);
    printf("%s [%s]: %s\n", time_buf, lvl_to_str(level), message);
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    if (!inputosm_set_log_callback(phony_log_callback))
    {
        puts("Invalid log callback set!");
        return 1;
    }
    inputosm_set_log_level(INPUTOSM_LOG_LEVEL_TRACE);
    puts("Log callback installed successfully!");
}