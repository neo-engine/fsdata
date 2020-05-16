NUM_LANGUAGES		?=   2
MAX_ITEMS_PER_DIR	?=  30
MAX_PKMN			?= 890
FSROOT				?= \"../../FSROOT/DATA\"
OUT					?= \"../../arm9/include\"

CC			=	g++
BUILD       :=	build
SOURCES     :=	source

CFLAGS      :=	-O2 -Wall -Werror -DNUM_LANGUAGES=$(NUM_LANGUAGES) \
				-DMAX_ITEMS_PER_DIR=$(MAX_ITEMS_PER_DIR) -DMAX_PKMN=$(MAX_PKMN) \
				-DFSROOT=$(FSROOT) -DOUT=$(OUT)
CXXFLAGS    :=	$(CFLAGS) -std=c++17
LDFLAGS     :=

CPPFILES	:=	fsdata.cpp
OFILES		:=	$(addprefix $(BUILD)/, $(CPPFILES:.cpp=.o) )

all: fsdata locationdata pkmndata

pkmndata: $(OFILES) $(BUILD)/pkmndata.o
	$(CC) $(LDFLAGS) -o $@ $^

locationdata: $(OFILES) $(BUILD)/locationdata.o
	$(CC) $(LDFLAGS) -o $@ $^

fsdata: locationdata pkmndata
	./locationdata data/locationnames.csv
	./pkmndata data/pkmnnames.csv data/abtynames.csv data/movenames.csv data/itemnames.csv \
		data/pkmndata.csv data/pkmndescr.csv data/pkmnformnames.csv data/pkmnformes.csv \
		data/itemdata_medicine.csv data/itemdata_formechange.csv data/itemdata_tmhm.csv \
		data/movedata.csv data/pkmnlearnsets.csv

clean:
	@rm -r $(BUILD)

$(BUILD)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJFILES:.o=.d)

