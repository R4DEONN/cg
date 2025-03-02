import AlchemyModel from "../Model/AlchemyModel";
import {AlchemyElementInstance, AlchemyElementTrait} from "../Model/AlchemyElement";
import EventDispatcher from "../EventDispatcher";
import Disposable from "../Disposable";

class AlchemyController extends Disposable {
	private _changeElementsOnTableEvent: EventDispatcher = new EventDispatcher();

	constructor(
		private _model: AlchemyModel,
	) {
		super();
		this.addHandler(_model.changeElementsOnTableEvent(), (elements: AlchemyElementInstance[]) => this._changeElementsOnTableEvent.dispatch(elements));
	}

	changeElementsOnTableEvent(): EventDispatcher {
		return this._changeElementsOnTableEvent;
	}

	getModel(): AlchemyModel {
		return this._model;
	}

	addElementOnTable(element: AlchemyElementTrait) {
		this._model.addElementOnTable(new AlchemyElementInstance(element, 100, 100));
	}

	setElementCoordinatesOnTable(element: AlchemyElementInstance, x: number, y: number) {
		this._model.setElementCoordinatesOnTable(element, x, y);
	}

	combineElements(firstElement: AlchemyElementInstance, secondElement: AlchemyElementInstance) {
		this._model.combineElements(firstElement, secondElement);
	}
}

export default AlchemyController;