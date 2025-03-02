import EventDispatcher from "./EventDispatcher";

class Disposable {
	private _disposables: Disposable[] = [];

	addHandler(eventDispatcher: EventDispatcher, handler: (...args: any[]) => any) {
		eventDispatcher.subscribe(handler);
	}

	addDisposable(disposable: Disposable) {
		this._disposables.push(disposable);
	}

	removeDisposable(disposableToRemove: Disposable) {
		this._disposables = this._disposables.filter(disposable => disposable !== disposableToRemove);
	}

	dispose() {
		this._disposables.forEach(disposable => disposable.dispose());
		this._disposables = [];
	}
}

export default Disposable;