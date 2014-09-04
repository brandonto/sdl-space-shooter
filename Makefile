ODIR = obj
SDIR = src
IDIR = include
PDIR = depend
BDIR = bin

_OBJS =	main.o \
		Application.o \
		ApplicationState.o \
		ApplicationStateManager.o \
		BackgroundRenderComponent.o \
		GameEntity.o \
		GameEntityCollection.o \
		GameEntityManager.o \
		IntroState.o \
		MenuState.o \
		SDL_util.o \
		UIPanelInputComponent.o \
		UIPanelRenderComponent.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

CC = g++

CFLAGS = -w -g

LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

PROG = SpaceShooter

all: $(OBJS)
	$(CC) $(CFLAGS) -I$(IDIR) -I$(BDIR) -o $(PROG) $^ $(LFLAGS)

$(ODIR)/%.o : $(SDIR)/%.cpp
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
#
#$(OBJSDIR)/ApplicationState.o: $(SRCSDIR)/ApplicationState.cpp \
#		$(INCDIR)/ApplicationState.h \
#		$(INCDIR)/ApplicationStateManager.h \
#		$(INCDIR)/WindowElements.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/ApplicationStateManager.o: $(SRCSDIR)/ApplicationStateManager.cpp \
#		$(INCDIR)/ApplicationStateManager.h \
#		$(INCDIR)/ApplicationState.h \
#		$(INCDIR)/MenuState.h \
#		$(INCDIR)/WindowElements.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/BackgroundRenderComponent.o: $(SRCSDIR)/BackgroundRenderComponent.cpp \
#		$(INCDIR)/BackgroundRenderComponent.h \
#		$(INCDIR)/RenderComponent.h \
#		$(INCDIR)/SDL_util.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/GameEntity.o: $(SRCSDIR)/GameEntity.cpp \
#		$(INCDIR)/GameEntity.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/GameEntityCollection.o: $(SRCSDIR)/GameEntityCollection.cpp \
#		$(INCDIR)/GameEntityCollection.h \
#		$(INCDIR)/GameEntity.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/GameEntityManager.o: $(SRCSDIR)/GameEntityManager.cpp \
#		$(INCDIR)/GameEntityManager.h \
#		$(INCDIR)/BackgroundRenderComponent.h \
#		$(INCDIR)/GameEntity.h \
#		$(INCDIR)/GameEntityCollection.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/IntroState.o: $(SRCSDIR)/IntroState.cpp \
#		$(INCDIR)/IntroState.h \
#		$(INCDIR)/ApplicationState.h \
#		$(INCDIR)/ApplicationStateManager.h \
#		$(INCDIR)/WindowElements.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/MenuState.o: $(SRCSDIR)/MenuState.cpp \
#		$(INCDIR)/MenuState.h \
#		$(INCDIR)/ApplicationState.h \
#		$(INCDIR)/ApplicationStateManager.h \
#		$(INCDIR)/GameEntityManager.h \
#		$(INCDIR)/WindowElements.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/main.o: $(SRCSDIR)/main.cpp \
#		$(INCDIR)/Application.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@
#
#$(OBJSDIR)/SDL_util.o: $(SRCSDIR)/SDL_util.cpp \
#		$(INCDIR)/SDL_util.h
#	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

