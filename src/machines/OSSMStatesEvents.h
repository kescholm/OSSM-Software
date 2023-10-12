#ifndef OSSM_SOFTWARE_OSSMSTATESEVENTS_H
#define OSSM_SOFTWARE_OSSMSTATESEVENTS_H

/**
 * This file defines the states and events for the OSSM.
 *
 * States are the different modes the OSSM can be in. For example, the OSSM
 * might be in the "homing" state, or the "menu" state.
 *
 * Events are the different things that can happen to the OSSM. For example, the
 * OSSM might receive a "button press" event, or a "homing complete" event.
 *
 * However, the OSSM may choose to not respond to an event. For example, if the
 * OSSM is in the "homing" state, it may choose to ignore a "button press".This
 * logic is controlled in the "handleEvent" method of the OSSM.
 *
 * Note: Any child machines of the OSSM can trigger and OSSM machine event, so
 * we must keep this file out of the OSSM class. This will prevent cyclical
 * imports.
 */
namespace OSSM_NS {

    enum class States {
        // None must always be defined as the first state.
        NONE,

        // Implement your states here.
        // Just make sure you manage state transitions in "handle event".
        INITIALIZING,
        HOMING,
        MENU,
        SIMPLE_STROKE,
        DEEPTHROAT_REPLAY,
        DEEPTHROAT_SPEED_REPLAY,

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };

    enum class Events {
        // None must always be defined as the first event type.
        NONE,

        // Implement your events here.

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };
}

#endif  // OSSM_SOFTWARE_OSSMSTATESEVENTS_H
