class EventDispatcher {
	private _handlers: Array<(...args: any[]) => any> = [];

	subscribe(fn: (...args: any[]) => any) {
		this._handlers.push(fn);
	}

	dispatch(...args: any[]) {
		this._handlers.forEach((handler) => handler(...args));
	}
}

export default EventDispatcher;