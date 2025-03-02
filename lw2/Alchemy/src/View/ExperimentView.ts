import Component from "../Component";
import Tag from "../Tag";
import AlchemyController from "../Controller/AlchemyController";
import AlchemyElement, {AlchemyElementInstance} from "../Model/AlchemyElement";
import ElementView from "./ElementView";
import {DragManager} from "./DragManager";
import elementView from "./ElementView";

class ExperimentView extends Component {
	private _elementsView: ElementView[] = [];

	constructor(
		private _controller: AlchemyController,
		private _dragManager = new DragManager(),
	) {
		super({
			blockName: 'experiment-view',
		});

		const title = new Component({
			blockTag: Tag.P,
		});
		title.setText("Поле для экспериментов");
		this.addChild(title);

		this.addHandler(_controller.changeElementsOnTableEvent(), (elements: AlchemyElementInstance[]) => this._renderElements(elements));
	}

	private _renderElements(elements: AlchemyElementInstance[]) {
		this._elementsView.forEach(elementView => this.removeDisposableChild(elementView));
		this._elementsView = [];
		elements.forEach(element => {
			const elementView = new ElementView(element.getTrait());
			elementView.setCoordinates(element.getCoordinates().x, element.getCoordinates().y);
			this._dragManager.enableForComponent(
				elementView, this.render(),
				(x, y) => {
					this._controller.setElementCoordinatesOnTable(element, x, y);

					const collidedElements = this._findCollision(elementView);
					collidedElements.forEach((collidedElement: ElementView) => {
						this._controller.combineElements(
							element,
							elements.find(collidedInstance => collidedInstance.getTrait() === collidedElement.getElement()) as AlchemyElementInstance,
						);
					})
				});
			this._elementsView.push(elementView);
			this.addChild(elementView);
		});
	}

	private _findCollision(targetElement: ElementView): ElementView[] {
		const targetRect = targetElement.render().getBoundingClientRect();

		return this._elementsView.filter(element => {
			if (element === targetElement) return false;
			const elementRect = element.render().getBoundingClientRect();
			return this._checkCollision(targetRect, elementRect);
		});
	}

	private _checkCollision(rect1: DOMRect, rect2: DOMRect): boolean {
		return !(
			rect1.right < rect2.left ||
			rect1.left > rect2.right ||
			rect1.bottom < rect2.top ||
			rect1.top > rect2.bottom
		);
	}
}

export default ExperimentView;