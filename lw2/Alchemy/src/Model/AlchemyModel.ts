import {AlchemyElementList} from "./ElementsList";
import AlchemyElement, {AlchemyElementInstance, AlchemyElementTrait} from "./AlchemyElement";
import EventDispatcher from "../EventDispatcher";
import {CombinationRule, CombinationRules} from "./CombinationRule";

class AlchemyModel {
	private _elements: AlchemyElement[] = AlchemyElementList;
	private _combinationRules: CombinationRule[] = CombinationRules;
	private _elementsOnTable: AlchemyElementInstance[] = [];
	private _changeElementsOnTableEvent: EventDispatcher = new EventDispatcher();
	private _changeElementListEvent: EventDispatcher = new EventDispatcher();

	changeElementsOnTableEvent(): EventDispatcher {
		return this._changeElementsOnTableEvent;
	}

	changeElementListEvent(): EventDispatcher {
		return this._changeElementListEvent;
	}

	getOpenElements(): AlchemyElement[] {
		return this._elements.filter(element => element.isOpen());
	}

	getElementsOnTable(): AlchemyElementInstance[] {
		return this._elementsOnTable;
	}

	addElementOnTable(element: AlchemyElementInstance) {
		this._elementsOnTable.push(element);
		this._changeElementsOnTableEvent.dispatch(this._elementsOnTable);
	}

	setElementCoordinatesOnTable(element: AlchemyElementInstance, x: number, y: number) {
		element.setCoordinates(x, y);
	}

	combineElements(firstElement: AlchemyElementInstance, secondElement: AlchemyElementInstance) {
		this._combinationRules.forEach((combinationRule: CombinationRule) => {
			if (combinationRule.ingredients.includes(firstElement.getName()) && combinationRule.ingredients.includes(secondElement.getName()))
			{
				combinationRule.results.forEach(result => {
					this._elements.forEach(element => {
						if (element.getName() == result)
						{
							element.setOpen(true);
							this._elementsOnTable.push(new AlchemyElementInstance(element.getTrait(), firstElement.getCoordinates().x, firstElement.getCoordinates().y))
						}

					});
				});

				this._elementsOnTable = this._elementsOnTable.filter(element => {
					return element.getName() !== firstElement.getName() && element.getName() !== secondElement.getName();
				});


				this._changeElementListEvent.dispatch(this._elements.filter(element => element.isOpen()));
				this._changeElementsOnTableEvent.dispatch(this._elementsOnTable);
			}
		});
	}
}

export default AlchemyModel;