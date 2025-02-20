import EventDispatcher from "./EventDispatcher";

class Disposable {
	addHandler(eventDispatcher: EventDispatcher, handler: (...args: any[]) => any) {
		eventDispatcher.subscribe(handler);
	}
}

export default Disposable;