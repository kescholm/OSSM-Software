//
// Created by Andrew Koenig on 2023-10-20.
//

#ifndef OSSM_SOFTWARE_STATELOGGER_H
#define OSSM_SOFTWARE_STATELOGGER_H

#include <WString.h>

#include <cassert>

#include "DebugLog.h"
#include "boost/sml.hpp"

namespace sml = boost::sml;
using namespace sml;

/**
 * OSSM State Logger
 *
 * This class is used to log state machine events.
 *
 * It is used by the OSSM class in OSSM.h.
 * By default this project will only show "LOG_DEBUG" and above.
 * You can change this in the platformio.ini file, or by added one of the
 * following build flags:
 *
 * -D LOG_LEVEL=LOG_LEVEL_NONE
 * -D LOG_LEVEL=LOG_LEVEL_ERROR
 * -D LOG_LEVEL=LOG_LEVEL_WARN
 * -D LOG_LEVEL=LOG_LEVEL_INFO
 * -D LOG_LEVEL=LOG_LEVEL_DEBUG
 * -D LOG_LEVEL=LOG_LEVEL_TRACE
 *
 */
struct StateLogger {
    template <class SM, class TEvent>
    [[gnu::used]] void log_process_event(const TEvent&) {
        LOG_TRACE(String(sml::aux::get_type_name<SM>()));
        String eventName = String(sml::aux::get_type_name<TEvent>());
        // if the event name starts with " boost::ext::sml" then only TRACE it
        // to reduce verbosity
        if (eventName.startsWith("boost::ext::sml")) {
            LOG_TRACE(eventName);
        } else {
            LOG_DEBUG(eventName);
        }
    }

    template <class SM, class TGuard, class TEvent>
    [[gnu::used]] void log_guard(const TGuard&, const TEvent&, bool result) {
        String resultString = result ? "[OK]" : "[FAIL]";
        LOG_TRACE(resultString + ": " + String(sml::aux::get_type_name<SM>()));
        LOG_DEBUG(resultString + ": " +
                  String(sml::aux::get_type_name<TGuard>()) + ", " +
                  String(sml::aux::get_type_name<TEvent>()));
    }

    template <class SM, class TAction, class TEvent>
    [[gnu::used]] void log_action(const TAction&, const TEvent&) {
        LOG_TRACE(String(sml::aux::get_type_name<SM>()));
        LOG_DEBUG(String(sml::aux::get_type_name<TAction>()) + ", " +
                  String(sml::aux::get_type_name<TEvent>()));
    }

    template <class SM, class TSrcState, class TDstState>
    [[gnu::used]] void log_state_change(const TSrcState& src,
                                        const TDstState& dst) {
        LOG_TRACE(String(sml::aux::get_type_name<SM>()));
        LOG_DEBUG(String(src.c_str()) + " -> " + String(dst.c_str()));
    }
};
#endif  // OSSM_SOFTWARE_STATELOGGER_H
