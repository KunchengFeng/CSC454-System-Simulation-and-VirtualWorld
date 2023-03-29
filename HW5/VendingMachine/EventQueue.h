#include "Event.h"
#pragma once

class EventQueue {
private:
	Event* head;

	int compareEvents(Event* event1, Event* event2) {
		if ((event1->time - event2->time) > 0.01) {
			return 1;
		}
		else if ((event1->time - event2->time) < -0.01) {
			return -1;
		}
		else {
			return 0;
		}
	}

public:
	EventQueue() { head = NULL; }

	void enqueue(Event * event) {

		if (head != NULL) {

			if (compareEvents(head, event) < 0) {						// Head comes before the event
				Event* current = head;
				while (true) {

					if (current->next != NULL) {

						if (compareEvents(current->next, event) < 0) {	// Current's next event happens earlier
							current = current->next;
						}
						else {											// Current's next event happens after
							Event* temp = current->next;
							current->next = event;
							event->next = temp;
							break;
						}
					}
					else {
						current->next = event;							// Current event don't have next event
						break;
					}
				}
			}
			else {														// Head comes after the event
				Event* temp = head;
				head = event;
				head->next = temp;
			}
		}
		else {															// Queue is empty
			head = event;
		}
	}

	Event* dequeue() {
		Event* event = head;
		head = head->next;
		return event;
	}

	bool hasNext() { return head != NULL;}
};