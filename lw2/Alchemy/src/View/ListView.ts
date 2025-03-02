import Component from "../Component";
import Tag from "../Tag";
import AlchemyController from "../Controller/AlchemyController";
import AlchemyElement from "../Model/AlchemyElement";
import ElementView from "./ElementView";

class ListView extends Component {
	private _elementList: Component;
	private _elements: Component[] = [];

	constructor(
		private _controller: AlchemyController
	) {
		super({
			blockName: "list-view",
		});

		const title = new Component({
			blockTag: Tag.P,
		});
		title.setText("Открытые элементы");
		this.addChild(title);

		this._elementList = this._createElementList(_controller.getModel().getOpenElements());
		this.addChild(this._elementList);

		this.addHandler(_controller.getModel().changeElementListEvent(), (elements: AlchemyElement[]) => this._createElementsView(elements, this._elementList))
	}

	private _createElementList(elements: AlchemyElement[]): Component {
		const table = new Component({
			blockName: this._createChildBemInfo('table'),
		});

		this._createElementsView(elements, table);

		return table;
	}

	private _createElementsView(elements: AlchemyElement[], table: Component): void {
		this._elements.forEach(element => table.removeChild(element));
		this._elements = [];
		elements.forEach(element => {
			const elementView = this._createElementView(element);
			this._elements.push(elementView);
			table.addChild(elementView);
		});
	}

	private _createElementView(element: AlchemyElement): ElementView {
		const elementView = new ElementView(element.getTrait());
		this.addHandler(elementView.clickEvent(), () => this._controller.addElementOnTable(element.getTrait()));
		this._elements.push(elementView);
		return elementView;
	}
}

export default ListView;