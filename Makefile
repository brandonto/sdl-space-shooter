ODIR = obj
SDIR = src
IDIR = include
PDIR = depend
BDIR = bin
DDIR = data

_OBJS =	main.o \
		Application.o \
		ApplicationState.o \
		ApplicationStateManager.o \
		BackgroundPhysicsComponent.o \
		BackgroundRenderComponent.o \
		BlackScreen.o \
		CollisionBodyRectangle.o \
		CollisionManager.o \
		CreditsState.o \
		EnemyCollisionComponent.o \
		EnemyRenderComponent.o \
		EnemyPhysicsComponent.o \
		EnemyProjectileCollisionComponent.o \
		EnemyProjectilePhysicsComponent.o \
		EnemyProjectileRenderComponent.o \
		ExplosionPhysicsComponent.o \
		ExplosionRenderComponent.o \
		FrameRateManager.o \
		GameEntity.o \
		GameEntityCollection.o \
		GameEntityData.o \
		GameEntityFactory.o \
		GameEntityManager.o \
		GameState.o \
		GameMenuState.o \
		InstructionsState.o \
		IntroState.o \
		MenuState.o \
		MeteorPhysicsComponent.o \
		MeteorRenderComponent.o \
		PauseState.o \
		PlayerCollisionComponent.o \
		PlayerInputComponent.o \
		PlayerInstructionsInputComponent.o \
		PlayerInstructionsPhysicsComponent.o \
		PlayerInstructionsProjectilePhysicsComponent.o \
		PlayerPhysicsComponent.o \
		PlayerRenderComponent.o \
		PlayerProjectileCollisionComponent.o \
		PlayerProjectilePhysicsComponent.o \
		PlayerProjectileRenderComponent.o \
		SDL_util.o \
		SpriteRenderComponent.o \
		StateEntityParser.o \
		TextRenderComponent.o \
		Texture.o \
		Timer.o \
		tinystr.o \
		tinyxml.o \
		tinyxmlerror.o \
		tinyxmlparser.o \
		UIClickFunction.o \
		UIPanelInputComponent.o \
		UIPanelRenderComponent.o \
		Vector2D.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

CC = g++

CFLAGS = -w -g

LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

PROG = SpaceShooter

all: $(OBJS)
	$(CC) $(CFLAGS) -I$(IDIR) -I$(BDIR) -I$(DDIR) -o $(PROG) $^ $(LFLAGS)

$(ODIR)/%.o : $(SDIR)/%.cpp
	@mkdir -p $(ODIR)
	@mkdir -p $(PDIR)
	$(CC) $(CFLAGS) -I$(IDIR) -MD -c -o $@ $<
	@cp $(ODIR)/$*.d $(PDIR)/$*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $(ODIR)/$*.d >> $(PDIR)/$*.P; \
		rm -f $(ODIR)/$*.d

-include $(PDIR)/*.P

clean:
	rm -f $(PROG) $(ODIR)/* $(PDIR)/*

#$(OBJSDIR)/Application.o: $(SRCSDIR)/Application.cpp \
#		$(INCDIR)/Application.h \
#		$(INCDIR)/ApplicationStateManager.h \
#		$(INCDIR)/SDL_util.h \
#		$(INCDIR)/WindowElements.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
