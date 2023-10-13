//
// Created by Andrew Koenig on 2023-10-13.
//

#ifndef OSSM_SOFTWARE_HOMESTATESEVENTS_H
#define OSSM_SOFTWARE_HOMESTATESEVENTS_H

namespace HOME_NS {

    enum class States {
        // None must always be defined as the first state.
        NONE,

        HOMING,

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };

    enum class Events {
        // None must always be defined as the first event type.
        NONE,

        // Finally, here's the size of the current state list.
        NUM_OPTIONS
    };
}
#endif  // OSSM_SOFTWARE_HOMESTATESEVENTS_H
