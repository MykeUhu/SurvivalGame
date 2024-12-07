// UhuAttributeSet.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UhuAttributeSet.generated.h"

// Makro für einfachen Zugriff auf Gameplay-Attribute
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// -------------------------
// Effekt-Eigenschaften-Struktur
// -------------------------

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    // Standardkonstruktor
    FEffectProperties() {}

    FGameplayEffectContextHandle EffectContextHandle; // Kontext des Effekts

    // Quell- und Zielinformationen
    UPROPERTY()
    UAbilitySystemComponent* SourceASC = nullptr;

    UPROPERTY()
    AActor* SourceAvatarActor = nullptr;

    UPROPERTY()
    AController* SourceController = nullptr;

    UPROPERTY()
    ACharacter* SourceCharacter = nullptr;

    UPROPERTY()
    UAbilitySystemComponent* TargetASC = nullptr;

    UPROPERTY()
    AActor* TargetAvatarActor = nullptr;

    UPROPERTY()
    AController* TargetController = nullptr;

    UPROPERTY()
    ACharacter* TargetCharacter = nullptr;
};

// Generischer Zeiger auf statische Funktionssignaturen
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * UUhuAttributeSet: Definiert die Gameplay-Attribute eines Charakters
 */
UCLASS()
class SURVIVALGAME_API UUhuAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    // Konstruktor
    UUhuAttributeSet();

    // Replikation von Eigenschaften
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Änderungen vor der Anpassung eines Attributs
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    // Verarbeitung nach der Anwendung eines Effekts
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    // Verarbeitung nach der Änderung eines Attributs
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    // Zuordnung von Gameplay-Tags zu Attributen
    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

    // -------------------------
    // Primär-Attribute
    // -------------------------

    /** Stärke */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Strength);

    // -------------------------
    // Lebens-Attribute
    // -------------------------

    /** Gesundheit */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Health);

    /** Maximale Gesundheit */
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, MaxHealth);

    // Effekt-Eigenschaften setzen
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

    // -------------------------
    // Replikations-Callbacks
    // -------------------------

    UFUNCTION()
    void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    // -------------------------
    // Zusätzliche Eigenschaften
    // -------------------------

    /** Flag zum Auffüllen der Gesundheit */
    bool bTopOffHealth = false;
};
