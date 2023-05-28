#include "ColorPreset.h"

FLinearColor UColorPreset::GetColor(bool SecondaryColor, bool ReserveColor, bool CardColor) const
{
	if(CardColor)
	{
		return ReserveColor ?
		SecondaryColor ? ReserveColorCard2 : ReserveColorCard1 :
		SecondaryColor ? ColorCard2 : ColorCard1;
	}
	return ReserveColor ?
		SecondaryColor ? ReserveColor2 : ReserveColor1 :
		SecondaryColor ? Color2 : Color1;
}

bool UColorPreset::HasSameColorTag(UColorPreset* Other) const
{
	return ColorTag.HasAny(Other->ColorTag);
}
