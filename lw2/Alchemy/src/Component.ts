import IView from "./View/IView";
import Tag from "./Tag";
import Disposable from "./Disposable";

type ComponentProps = {
	blockName?: string;
	blockTag?: string;
}

class Component extends Disposable implements IView {
	private _content: HTMLElement;

	constructor({blockName = '', blockTag = Tag.DIV}: ComponentProps) {
		super();

		this._content = document.createElement(blockTag);
		this._content.className = blockName;
	}

	addChild(child: IView): void {
		this._content.appendChild(child.render());
	}

	setText(text: string): void {
		this._content.textContent = text;
	}

	render(): HTMLElement {
		return this._content;
	}
}

export default Component;