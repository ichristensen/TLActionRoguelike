// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	Health = 100;
}

bool UAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
	return true;
}

