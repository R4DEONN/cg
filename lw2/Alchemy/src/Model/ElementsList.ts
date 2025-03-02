import AlchemyElement, {AlchemyElementTrait} from "./AlchemyElement";

enum AlchemyElementType {
	FIRE = 'Огонь',
	WATER = 'Вода',
	EARTH = 'Земля',
	AIR = 'Воздух',
	STEAM = 'Пар',
	LAVA = 'Лава',
	DUST = 'Пыль',
	POWDER = 'Порох',
	EXPLOSION = 'Взрыв',
	SMOKE = 'Дым',
	ENERGY = 'Энергия',
	STONE = 'Камень',
	STORM = 'Буря',
	METAL = 'Метал',
}

const ElementTypeToImagePathMap: Record<string, string> = {
	[AlchemyElementType.FIRE]: '/images/fire.png',
	[AlchemyElementType.WATER]: '/images/water.png',
	[AlchemyElementType.EARTH]: '/images/earth.png',
	[AlchemyElementType.AIR]: '/images/air.png',
	[AlchemyElementType.STEAM]: '/images/steam.png',
	[AlchemyElementType.LAVA]: '/images/lava.png',
	[AlchemyElementType.DUST]: '/images/dust.png',
	[AlchemyElementType.POWDER]: '/images/powder.png',
	[AlchemyElementType.EXPLOSION]: '/images/explosion.png',
	[AlchemyElementType.SMOKE]: '/images/smoke.png',
	[AlchemyElementType.ENERGY]: '/images/energy.png',
	[AlchemyElementType.STONE]: '/images/stone.png',
	[AlchemyElementType.STORM]: '/images/storm.png',
	[AlchemyElementType.METAL]: '/images/metal.png',
}

const AlchemyElementTraitList = [
	new AlchemyElementTrait(AlchemyElementType.FIRE),
	new AlchemyElementTrait(AlchemyElementType.WATER),
	new AlchemyElementTrait(AlchemyElementType.EARTH),
	new AlchemyElementTrait(AlchemyElementType.AIR),
	new AlchemyElementTrait(AlchemyElementType.STEAM),
	new AlchemyElementTrait(AlchemyElementType.LAVA),
	new AlchemyElementTrait(AlchemyElementType.DUST),
	new AlchemyElementTrait(AlchemyElementType.POWDER),
	new AlchemyElementTrait(AlchemyElementType.EXPLOSION),
	new AlchemyElementTrait(AlchemyElementType.SMOKE),
	new AlchemyElementTrait(AlchemyElementType.ENERGY),
	new AlchemyElementTrait(AlchemyElementType.STONE),
	new AlchemyElementTrait(AlchemyElementType.STORM),
	new AlchemyElementTrait(AlchemyElementType.METAL),
];

const StartupElements: string[] = [AlchemyElementType.FIRE, AlchemyElementType.WATER, AlchemyElementType.EARTH, AlchemyElementType.AIR];

const AlchemyElementList: AlchemyElement[] = [];
AlchemyElementTraitList.forEach(elementTrait => {
	AlchemyElementList.push(new AlchemyElement(elementTrait, StartupElements.includes(elementTrait.getName())));
});

export {AlchemyElementTraitList, AlchemyElementList, AlchemyElementType, ElementTypeToImagePathMap};