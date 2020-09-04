NUM_LANGUAGES		?=   2
MAX_ITEMS_PER_DIR	?=  30
MAX_PKMN			?= 893
ifdef LOCAL
FSROOT				?= out/FSROOT
OUT					?= out/include
else
FSROOT				?= ../../FSROOT/DATA
OUT					?= ../../arm9/include
endif

CC			=	g++
BUILD       :=	build
SOURCES     :=	source
DATA     	:=	data

CFLAGS      :=	-O2 -Wall -DNUM_LANGUAGES=$(NUM_LANGUAGES) \
				-DMAX_ITEMS_PER_DIR=$(MAX_ITEMS_PER_DIR) -DMAX_PKMN=$(MAX_PKMN) \
				-DFSROOT=\"$(FSROOT)\" -DOUT=\"$(OUT)\"
CXXFLAGS    :=	$(CFLAGS) -std=c++2a
LDFLAGS     :=

MAPSCRIPT_FILES	:= $(addprefix $(DATA)/scripts/, $(foreach dir, $(DATA)/scripts,$(notdir $(wildcard $(dir)/*.m4.h))))
MAPDATA_FILES	:= $(addprefix $(DATA)/map/, $(foreach dir, $(DATA)/map,$(notdir $(wildcard $(dir)/*.mdata))))
TRAINERDATA_FILES	:= $(addprefix $(DATA)/trainer/, $(foreach dir, $(DATA)/trainer,$(notdir $(wildcard $(dir)/*.tdata))))
DATA_FILES	:=  $(addprefix $(DATA)/, $(foreach dir, $(DATA),$(notdir $(wildcard $(dir)/*.csv))))
CPPFILES	:=	fsdata.cpp
OFILES		:=	$(addprefix $(BUILD)/, $(CPPFILES:.cpp=.o) )

fsdata: locationdata pkmndata evolutiondata trainerdata mapdata mapscript $(DATA_FILES)
ifdef LOCAL
	@mkdir -p $(FSROOT)
	@mkdir -p $(OUT)
endif
	@mkdir -p $(BUILD)
	./locationdata data/locationnames.csv
	./pkmndata data/pkmnnames.csv data/abtynames.csv data/movenames.csv data/itemnames.csv \
		data/pkmndata.csv data/pkmndescr.csv data/pkmnformnames.csv data/pkmnformes.csv \
		data/itemdata_medicine.csv data/itemdata_formechange.csv data/itemdata_tmhm.csv \
		data/movedata.csv data/pkmnlearnsets.csv data/abtydescr.csv data/movedescr.csv \
		data/itemflavor.csv data/pkmncategory.csv data/pkmnflavor.csv data/itemdata.csv \
		data/trainerclassnames.csv
	./evolutiondata data/pkmnnames.csv data/abtynames.csv data/movenames.csv data/itemnames.csv \
		data/locationnames.csv data/pkmnevolv.csv
	@$(foreach tdata,$(TRAINERDATA_FILES),./trainerdata data/pkmnnames.csv data/abtynames.csv \
		data/movenames.csv data/itemnames.csv data/trainerclassnames.csv $(tdata);)
	@$(foreach mdata,$(MAPDATA_FILES),./mapdata data/pkmnnames.csv data/itemnames.csv \
		data/locationnames.csv $(mdata);)
	@$(foreach mscr,$(MAPSCRIPT_FILES),$(CC) -E -P -I$(SOURCES) -I$(OUT) $(mscr) | m4 > $(mscr).script; ./mapscript $(mscr).script;)
	touch fsdata

mapscript: $(OFILES) $(BUILD)/mapscript.o
	$(CC) $(LDFLAGS) -o $@ $^

pkmndata: $(OFILES) $(BUILD)/pkmndata.o
	$(CC) $(LDFLAGS) -o $@ $^

locationdata: $(OFILES) $(BUILD)/locationdata.o
	$(CC) $(LDFLAGS) -o $@ $^

evolutiondata: $(OFILES) $(BUILD)/pkmnevolv.o
	$(CC) $(LDFLAGS) -o $@ $^

trainerdata: $(OFILES) $(BUILD)/trainerdata.o
	$(CC) $(LDFLAGS) -o $@ $^

mapdata: $(OFILES) $(BUILD)/mapdata.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	@rm -r $(BUILD)
	@rm fsdata
	@rm locationdata
	@rm evolutiondata
	@rm pkmndata
	@rm mapdata

$(BUILD)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJFILES:.o=.d)

