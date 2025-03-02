import Disposable from "../Disposable";
import Component from "../Component";

export class DragManager extends Disposable {
	private _isDragging: boolean = false;
	private _startX: number = 0;
	private _startY: number = 0;
	private _currentComponent: Component | null = null;
	private _currentBoundsContainer: HTMLElement | null = null;
	private _onDropMap: Map<Component, (x: number, y: number) => void> = new Map();

	constructor(
	) {
		super();
		this._setupGlobalListeners();
	}

	enableForComponent(
		component: Component,
		boundsContainer: HTMLElement, // Добавляем параметр контейнера
		onDrop: (x: number, y: number) => void
	): void {
		const element = component.render();
		element.style.position = 'absolute';
		element.addEventListener('mousedown', (e) => this.handleMouseDown(e, component, boundsContainer));
		this._onDropMap.set(component, onDrop);
	}

	private _setupGlobalListeners(): void {
		document.addEventListener('mousemove', this.handleMouseMove);
		document.addEventListener('mouseup', this.handleMouseUp);
	}

	private handleMouseDown = (
		e: MouseEvent,
		component: Component,
		boundsContainer: HTMLElement // Добавляем параметр границ
	): void => {
		this._isDragging = true;
		this._currentComponent = component;
		this._currentBoundsContainer = boundsContainer;

		const rect = component.getCoordinates();
		this._startX = e.clientX - rect.x;
		this._startY = e.clientY - rect.y;
	};

	// Добавляем поле для хранения границ

	private handleMouseMove = (e: MouseEvent): void => {
		if (!this._isDragging || !this._currentComponent || !this._currentBoundsContainer) return;

		let newX = e.clientX - this._startX;
		let newY = e.clientY - this._startY;

		const element = this._currentComponent.render();

		// Рассчитываем границы
		const maxX = this._currentBoundsContainer.getBoundingClientRect().width - element.offsetWidth;
		const maxY = this._currentBoundsContainer.getBoundingClientRect().height - element.offsetHeight;

		newX = Math.max(0, Math.min(newX, maxX));
		newY = Math.max(0, Math.min(newY, maxY));

		this._currentComponent.setCoordinates(newX, newY);
	};

	private handleMouseUp = (e: MouseEvent): void => {
		if (!this._isDragging) return;

		const onDrop = this._onDropMap.get(this._currentComponent!);
		onDrop && onDrop(this._currentComponent!.getCoordinates().x, this._currentComponent!.getCoordinates().y );

		this._isDragging = false;
		this._currentComponent = null;
	};
}