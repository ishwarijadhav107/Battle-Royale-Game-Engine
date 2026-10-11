#include "environment/EnvironmentEvent.h"
#include <iostream>

void EnvironmentEventLog::record(const std::string& type, const std::string& description) {
    events.push_back({type, description});
}
const std::vector<EnvironmentEvent>& EnvironmentEventLog::getEvents() const { return events; }
void EnvironmentEventLog::displayEvents() const {
    if (events.empty()) { std::cout << "No environment events recorded.\n"; return; }
    for (std::size_t i = 0; i < events.size(); ++i)
        std::cout << i + 1 << ". [" << events[i].type << "] " << events[i].description << "\n";
}
void EnvironmentEventLog::clear() { events.clear(); }
