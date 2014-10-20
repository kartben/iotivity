/* debug.h -- debug utilities
 *
 * Copyright (C) 2010,2011 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the CoAP library libcoap. Please see
 * README for terms of use. 
 */

#ifndef _COAP_DEBUG_H_
#define _COAP_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

#ifndef COAP_DEBUG_FD
#define COAP_DEBUG_FD stdout
#endif

#ifndef COAP_ERR_FD
#define COAP_ERR_FD stderr
#endif

#ifdef HAVE_SYSLOG_H
#include <syslog.h>
typedef short coap_log_t;
#else
/** Pre-defined log levels akin to what is used in \b syslog. */
typedef enum { LOG_EMERG=0, LOG_ALERT, LOG_CRIT, LOG_WARNING, 
       LOG_NOTICE, LOG_INFO, LOG_DEBUG
} coap_log_t;
#endif



/** Returns the current log level. */
coap_log_t coap_get_log_level();

/** Sets the log level to the specified value. */
void coap_set_log_level(coap_log_t level);

/** 
 * Writes the given text to @c COAP_ERR_FD (for @p level <= @c
 * LOG_CRIT) or @c COAP_DEBUG_FD (for @p level >= @c LOG_WARNING). The
 * text is output only when @p level is below or equal to the log
 * level that set by coap_set_log_level().
 */
void coap_log_impl(coap_log_t level, const char *format, ...);

#ifndef coap_log
#define coap_log(...) coap_log_impl(__VA_ARGS__)
#endif

#ifndef TB_LOG
#define NDEBUG
#endif

#ifndef NDEBUG

/* A set of convenience macros for common log levels. */
#define info(...) coap_log(LOG_INFO, __VA_ARGS__)
#define warn(...) coap_log(LOG_WARNING, __VA_ARGS__)
#define debug(...) coap_log(LOG_DEBUG, __VA_ARGS__)

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#include "pdu.h"
void coap_show_pdu(const coap_pdu_t *);

#ifdef WITH_ANDROID
/* For the Android build, the compiler does not likes these declarations */
struct coap_address_t;
size_t coap_print_addr(const struct coap_address_t *, unsigned char *, size_t);
#endif

#else

#define debug(...)
#define info(...)
#define warn(...)

#define TODO(x)
#define coap_show_pdu(x)
#define coap_print_addr(...)

#endif

#ifdef __cplusplus
}
#endif

#endif /* _COAP_DEBUG_H_ */