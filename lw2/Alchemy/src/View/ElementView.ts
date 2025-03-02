import AlchemyElement, {AlchemyElementInstance, AlchemyElementTrait} from "../Model/AlchemyElement";
import Component from "../Component";
import Tag from "../Tag";
import {ElementTypeToImagePathMap} from "../Model/ElementsList";

class ElementView extends Component {
	constructor(
		private _element: AlchemyElementTrait
	) {
		super({
			blockName: 'element',
		});

		const image = new Component({
			blockTag: Tag.IMAGE,
			blockName: this._createChildBemInfo('image'),
		});
		image.setAttribute('src', ElementTypeToImagePathMap[_element.getName()]);
		this.addChild(image);

		const title = new Component({
			blockTag: Tag.P,
			blockName: this._createChildBemInfo('title'),
		});
		title.setText(_element.getName());
		this.addChild(title);
	}

	getElement(): AlchemyElementTrait {
		return this._element;
	}
}

export default ElementView;