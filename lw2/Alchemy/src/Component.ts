import IView from "./View/IView";
import Tag from "./Tag";
import Disposable from "./Disposable";
import EventDispatcher from "./EventDispatcher";
import {AlchemyElementTrait} from "./Model/AlchemyElement";
import disposable from "./Disposable";

type ComponentProps = {
	blockName?: string;
	blockTag?: string;
}

class Component extends Disposable implements IView {
	private _content: HTMLElement;
	private _clickEvent: EventDispatcher = new EventDispatcher();

	constructor({blockName = '', blockTag = Tag.DIV}: ComponentProps = {}) {
		super();

		this._content = document.createElement(blockTag);
		this._content.className = blockName;

		this._content.addEventListener('click', () => this._clickEvent.dispatch());
	}

	clickEvent(): EventDispatcher {
		return this._clickEvent;
	}

	addChild(child: IView): void {
		this._content.appendChild(child.render());
	}

	removeChild(child: IView): void {
		const childElement = child.render();
		if (this._content.contains(childElement))
		{
			this._content.removeChild(childElement);
		}
	}

	addDisposableChild(component: Component) {
		this.addDisposable(component);
		this.addChild(component);
	}

	removeDisposableChild(component: Component) {
		this.removeDisposable(component);
		this.removeChild(component);
	}

	setText(text: string): void {
		this._content.textContent = text;
	}

	render(): HTMLElement {
		return this._content;
	}

	setAttribute(attribute: string, value: string): void {
		this._content.setAttribute(attribute, value);
	}

	setCoordinates(x: number, y: number): void {
		this._content.style.left = `${x}px`;
		this._content.style.top = `${y}px`;
	}

	getCoordinates(): {x: number, y: number} {
		return {
			x: parseFloat(this._content.style.left) || 0,
			y: parseFloat(this._content.style.top) || 0
		};
	}

	protected _createChildBemInfo(className: string): string {
		return `${this._content.className}__${className}`;
	}

	dispose() {
		super.dispose();
	}
}

export default Component;