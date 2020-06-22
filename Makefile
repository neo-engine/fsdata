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

DATA_FILES	:=  $(addprefix $(DATA)/, $(foreach dir, $(DATA),$(notdir $(wildcard $(dir)/*.csv))))
CPPFILES	:=	fsdata.cpp
OFILES		:=	$(addprefix $(BUILD)/, $(CPPFILES:.cpp=.o) )

fsdata: locationdata pkmndata $(DATA_FILES)
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
		data/itemflavor.csv
	touch fsdata

pkmndata: $(OFILES) $(BUILD)/pkmndata.o
	$(CC) $(LDFLAGS) -o $@ $^

locationdata: $(OFILES) $(BUILD)/locationdata.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	@rm -r $(BUILD)
	@rm fsdata
	@rm locationdata
	@rm pkmndata

$(BUILD)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJFILES:.o=.d)

