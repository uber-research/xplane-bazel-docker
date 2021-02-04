#!/usr/bin/env python3
import pyautogui
import time

def click_on(pic_name: str) -> None:
    """Locate picture on screen and click on it
    """
    pos = pyautogui.locateCenterOnScreen(f'assets/{pic_name}.png')
    if pos is not None:
        pyautogui.moveTo(pos[0], pos[1])
        pyautogui.click()
    else:
        raise RuntimeError(f'Cannot locate image {pic_name} on screen')

def install_demo() -> None:
    click_on('xplane_install_demo')
    click_on('xplane_agree_terms_eula')
    click_on('xplane_send_diagnostic')
    click_on('xplane_continue')
    time.sleep(1.5)
    pyautogui.click()

if __name__ == "__main__":
    install_demo()
