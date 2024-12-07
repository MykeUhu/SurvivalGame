// Copyright by MykeUhu


#include "Game/UI/Widget/UhuUserWidget.h"

void UUhuUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
