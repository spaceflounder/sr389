TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lphysfs `pkg-config --libs --static allegro-5 allegro_audio-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_acodec-5 allegro_primitives-5 allegro_physfs-5`

SOURCES += \
    game/game.c \
    game/mario.c \
    game/monsters/goomba.c \
    game/monsters/cannon.c \
    game/coin.c \
    game/monsters/plant.c \
    game/monsters/koopa.c \
    game/monsters/anvil.c \
    game/monsters/penguin.c \
    game/monsters/shyguy.c \
    game/monsters/bat.c \
    game/monsters/bobomb.c \
    game/monsters/flyingkoopa.c \
    game/hud.c \
    game/stages/castle1.c \
    game/monsters/firebar.c \
    game/monsters/lakitu.c \
    game/bridge.c \
    game/levelexit.c \
    game/monsters/bowser.c \
    game/monsters/pokey.c \
    game/overworld.c \
    game/tickerprint.c \
    game/monsters/pow.c \
    game/gamemenus.c \
    game/jumpblock.c \
    game/stages/desert01.c \
    game/stages/travelToad.c \
    game/toad.c \
    game/babyyoshi.c \
    game/monsters/thwomp.c \
    game/monsters/birdo.c \
    game/stages/stageA01.c \
    game/pswitch.c \
    game/stages/stageA03.c \
    game/stages/castle2.c \
    game/monsters/blooper.c \
    game/stages/seaside1.c \
    game/water.c \
    game/monsters/fryguy.c \
    camera.c \
    control.c \
    cutscene.c \
    font.c \
    hitbox.c \
    main.c \
    medlib.c \
    menu.c \
    particle.c \
    sound.c \
    sprite.c \
    state.c \
    tile.c \
    video.c \
    game/elevator.c \
    game/monsters/poisonmushroom.c \
    game/stages/josiah.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    video.h \
    state.h \
    sprite.h \
    control.h \
    sound.h \
    font.h \
    anim.h \
    hitbox.h \
    game/mario.h \
    medlib.h \
    camera.h \
    game/game.h \
    tile.h \
    game/stages/jeff1.h \
    game/stages/jeff2.h \
    game/stages/josh1.h \
    game/stages/kira.h \
    game/stages/pyramid.h \
    game/stages/stageA03.h \
    game/stages/stageC02.h \
    game/stages/stageD01.h \
    game/stages/stageU01.h \
    game/stages/stageU02.h \
    game/stages/stageU03.h \
    game/monsters/monsters.h \
    game/coin.h \
    game/monsters/bowser.h \
    game/monsters/koopa.h \
    plant.h \
    particle.h \
    game/monsters/penguin.h \
    game/monsters/shyguy.h \
    cutscene.h \
    game/bridge.h \
    game/overworld/flag.h \
    game/monsters/fire.h \
    game/monsters/verticalfire.h \
    game/monsters/pokey.h \
    game/flag.h \
    game/tickerprint.h \
    menu.h \
    game/stages/castle1.h \
    game/monsters/penguindisguise.h \
    game/toad.h \
    game/yoshi.h \
    game/stages/traveltoad.h \
    game/monsters/thwomp.h \
    game/monsters/birdo.h \
    game/stages/stagea01.h \
    pswitch.h \
    game/monsters/luigi.h \
    game/stages/stageA03.h \
    game/stages/castle2.h \
    game/monsters/blooper.h \
    game/stages/seaSide1.h \
    game/monsters/fryguy.h \
    game/qb.h

