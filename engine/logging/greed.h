#ifndef GREED_LOGGER_H
#define GREED_LOGGER_H
/*
 * Greed is a basic logging library, utilizing useful logs for informing a
 * developer based on different levels of logging and colorizing them to ensure
 * readability. Being GREEDY with everything involved in the code.
 */

#include <stdio.h>
#include <time.h>

/* --- GREED LOGGER --- */
typedef enum { LOG_DBG, LOG_SCS, LOG_WRN, LOG_ERR, LOG_LVL_LEN } LOG_LEVEL;

void g_logger(LOG_LEVEL lvl, const char *msg, char *file, int line);
#endif // GREED_LOGGER_H

// IMPLEMENTATION
#ifdef GREED_IMPLEMENTATION
static const char *DEFAULT_COLOR = "\x1b[0m";

static char *type[LOG_LVL_LEN] = {"DEBUG", "SUCCESS", "WARNING", "ERROR"};
static char *colors[LOG_LVL_LEN] = {
    "\x1b[34m", /* blue */
    "\x1b[32m", /* green */
    "\x1b[33m", /* yellow */
    "\x1b[31m"  /* red */
};
static time_t current_time;
static struct tm *m_time;

static void get_time() {
  time(&current_time);
  m_time = localtime(&current_time);
}

void g_logger(LOG_LEVEL lvl, const char *msg, char *file, int line) {
  get_time();
  printf("%s", colors[lvl]);
  printf("[%s]", type[lvl]);
  printf("[%d/%d/%d -> %d:%d:%d]--", m_time->tm_mday, m_time->tm_mon,
    m_time->tm_year + 1900, m_time->tm_hour, m_time->tm_min,
    m_time->tm_sec);
    printf("[%s on line %u in file %s]\n%s", msg, line, file, DEFAULT_COLOR);
}

#define g_log_debug(msg)   g_logger(LOG_DBG, msg, __FILE__, __LINE__);
#define g_log_success(msg) g_logger(LOG_SCS, msg, __FILE__, __LINE__);
#define g_log_warning(msg) g_logger(LOG_WRN, msg, __FILE__, __LINE__);
#define g_log_error(msg)   g_logger(LOG_ERR, msg, __FILE__, __LINE__);

#endif // GREED_IMPLEMENTATION