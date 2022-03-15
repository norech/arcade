/**
 * @version 0.1
 * @date 2022-03-09
 */
#pragma once

namespace arc {

/**
 * @brief Common - The event class.
 * @details This class is used to represent an event.
 */
class Event {
public:
    struct KeyboardInputEvent {
        /**
         * @brief The key that was pressed.
         */
        int keyCode;
    };

    enum EventType { UNKNOWN = 0, QUIT = 1, KEYDOWN = 2, COUNT };

    EventType type;

    union {
        KeyboardInputEvent keyboardInput;
    };
};

}  // namespace arc
