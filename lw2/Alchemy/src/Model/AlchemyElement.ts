class AlchemyElement {
	private _isOpen: boolean = false;

	constructor(
		private _name: string,
		private _iconSvg: string,
	) {}

	getName(): string {
		return this._name;
	}

	getIconSvg(): string {
		return this._iconSvg;
	}

	isOpen(): boolean {
		return this._isOpen;
	}

	setOpen(value: boolean): void {
		this._isOpen = value;
	}
}

export default AlchemyElement;