// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisBlock.h"

// Sets default values
ATetrisBlock::ATetrisBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>("BlockMesh");
	RootComponent = BlockMesh;

}

// Called when the game starts or when spawned
void ATetrisBlock::BeginPlay()
{
	Super::BeginPlay();


    for (int i = 0; i < BlockMesh->GetNumMaterials(); i++)
    {
        UMaterialInterface* Material = BlockMesh->GetMaterial(i);
        if (!Material) return;

        UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

        BlockMesh->SetMaterial(0, DynamicMaterial);

        DynamicMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Gray);
    }

}

// Called every frame
void ATetrisBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATetrisBlock::GetMeshSize() const
{
	return BlockMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();
}

void ATetrisBlock::SetColor(FLinearColor _Color)
{
    for (int i = 0; i < BlockMesh->GetNumMaterials(); i++)
    {
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(BlockMesh->GetMaterial(i));
		if (nullptr != DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(FName("Color"), _Color);
		}
    }
}



