export class AlchemyElementTrait {
	constructor(
		private _name: string,
	) {
	}

	getName(): string {
		return this._name;
	}
}

export class AlchemyElementInstance {
	constructor(
		private _trait: AlchemyElementTrait,
		private _x: number,
		private _y: number,
	) {
	}

	getTrait() {
		return this._trait;
	}

	getName(): string {
		return this._trait.getName();
	}

	setCoordinates(x: number, y: number) {
		this._x = x;
		this._y = y;
	}

	getCoordinates(): {x: number, y: number} {
		return {x: this._x, y: this._y};
	}
}

class AlchemyElement {
	constructor(
		private _trait: AlchemyElementTrait,
		private _isOpen: boolean = false,
	) {}

	getTrait(): AlchemyElementTrait {
		return this._trait;
	}

	getName(): string {
		return this._trait.getName();
	}

	isOpen(): boolean {
		return this._isOpen;
	}

	setOpen(value: boolean): void {
		this._isOpen = value;
	}
}

export default AlchemyElement;