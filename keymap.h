#ifndef KEYMAP_H
#define KEYMAP_H


/* external interface to keymapper code */
void setKeymapPauseMsg(char *msg);
void setReturnState(void (*returnState)(struct CONTROLLER *controller));
void setHardwareControl(struct HWCONTROLINPUT *hwc);
void mapButton(int buttonIndex);

#endif // KEYMAP_H

