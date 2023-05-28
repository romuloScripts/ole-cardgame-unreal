// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetComponentCustomCollision.h"

FCollisionShape UWidgetComponentCustomCollision::GetCollisionShape(float Inflation) const
{
	if ( Space != EWidgetSpace::Screen )
	{
		FVector BoxHalfExtent = ( FVector(0.01f, CollisionArea.X * 0.5f, CollisionArea.Y * 0.5f) * GetComponentTransform().GetScale3D() ) + Inflation;

		if ( Inflation < 0.0f )
		{
			// Don't shrink below zero size.
			BoxHalfExtent = BoxHalfExtent.ComponentMax(FVector::ZeroVector);
		}

		return FCollisionShape::MakeBox(BoxHalfExtent);
	}
	else
	{
		return FCollisionShape::MakeBox(FVector::ZeroVector);
	}
}

void UWidgetComponentCustomCollision::BeginPlay()
{
	Super::BeginPlay();
	UpdateCollision();
}

void UWidgetComponentCustomCollision::UpdateCollision()
{
	BodySetup = NewObject<UBodySetup>(this);
	BodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
	BodySetup->AggGeom.BoxElems.Add(FKBoxElem());

	FKBoxElem* BoxElem = BodySetup->AggGeom.BoxElems.GetData();

	const float Width = CollisionArea.X;
	const float Height = CollisionArea.Y;
	const FVector Origin = FVector(.5f,
		-( Width * 0.5f ) + ( Width * Pivot.X ),
		-( Height * 0.5f ) + ( Height * Pivot.Y ));
		
	BoxElem->X = 0.01f;
	BoxElem->Y = Width;
	BoxElem->Z = Height;

	BoxElem->SetTransform(FTransform::Identity);
	BoxElem->Center = Origin;
	RecreatePhysicsState();
}
