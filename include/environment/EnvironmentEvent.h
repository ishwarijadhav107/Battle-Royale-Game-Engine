#ifndef ENVIRONMENT_EVENT_H
#define ENVIRONMENT_EVENT_H

#include <string>
#include <vector>

/** Simple event record that the game engine can display or store. */
struct EnvironmentEvent {
    std::string type;
    std::string description;
};

class EnvironmentEventLog {
private:
    std::vector<EnvironmentEvent> events;
public:
    void record(const std::string& type, const std::string& description);
    const std::vector<EnvironmentEvent>& getEvents() const;
    void displayEvents() const;
    void clear();
};
#endif
