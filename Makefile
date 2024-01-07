NUM_LANGUAGES		?=   2
MAX_ITEMS_PER_DIR	?=  30
ACHIEVEMENT_LEN		?= 100
UISTRING_LEN		?= 250
MAPSTRING_LEN		?= 800
MGSTRING_LEN		?= 500
PKMNPHRS_LEN		?= 150
BADGENAME_LEN		?=  50
RIBBONNAME_LEN		?=  50
RIBBONDSCR_LEN		?= 250
TRNNAME_LEN			?=  16
PKMNNAME_LEN		?=  14
TRNMSG_LEN			?= 200
EASYPHRS_LEN		?= 200
EASYWORD_LEN		?= 40

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

CFLAGS      :=	-Wall -DNUM_LANGUAGES=$(NUM_LANGUAGES) \
				-DMAX_ITEMS_PER_DIR=$(MAX_ITEMS_PER_DIR) \
				-DFSROOT=\"$(FSROOT)\" -DOUT=\"$(OUT)\" -g3 -ggdb
CXXFLAGS    :=	$(CFLAGS) -std=c++2b
LDFLAGS     :=

MAPSCRIPT_FILES	:= $(addprefix $(DATA)/scripts/, $(foreach dir, $(DATA)/scripts,$(notdir $(wildcard $(dir)/*.m4.h))))
MAPDATA_FILES	:= $(addprefix $(DATA)/map/, $(foreach dir, $(DATA)/map,$(notdir $(wildcard $(dir)/*.mdata))))
TRAINERDATA_FILES	:= $(addprefix $(DATA)/trainer/, $(foreach dir, $(DATA)/trainer,$(notdir $(wildcard $(dir)/*.tdata))))
DATA_FILES	:=  $(addprefix $(DATA)/, $(foreach dir, $(DATA),$(notdir $(wildcard $(dir)/*.csv))))
CPPFILES	:=	fsdata.cpp
OFILES		:=	$(addprefix $(BUILD)/, $(CPPFILES:.cpp=.o) )

fsdata: locationdata pkmndata trainerdata mapdata mapscript stringconv easyChat battleFrontier battleFrontierTrainer $(DATA_FILES)
ifdef LOCAL
	@mkdir -p $(FSROOT)
	@mkdir -p $(OUT)
endif
	@mkdir -p $(BUILD)
	./locationdata data/bgmnames.csv data/locationnames.csv data/locationdata.csv data/bgm/
	./pkmndata data/pkmnnames.csv data/abtynames.csv data/movenames.csv data/itemnames.csv \
		data/pkmndata.csv data/pkmndescr.csv data/pkmnformnames.csv data/pkmnformes.csv \
		data/itemdata_medicine.csv data/itemdata_formechange.csv data/itemdata_tmhm.csv \
		data/movedata.csv data/pkmnlearnsets.csv data/abtydescr.csv data/movedescr.csv \
		data/itemflavor.csv data/pkmncategory.csv data/pkmnflavor.csv data/itemdata.csv \
		data/trainerclassnames.csv data/pkmnevolv.csv data/locationnames.csv \
		data/pkmnformlearnsets.csv data/berrydata.csv
	./battleFrontier data/pkmnnames.csv data/movenames.csv data/itemnames.csv \
		data/bfpokemondata.csv "bfpoke.datab"
	./battleFrontierTrainer data/trainerclassnames.csv data/bftrainerdata.csv "bftrainer.datab"
	./battleFrontier data/pkmnnames.csv data/movenames.csv data/itemnames.csv \
		data/bfpokemondata_tent.csv "bfpoket.datab"
	./stringconv data/strings/strings.csv "STRN/UIS/" "uis" $(UISTRING_LEN)
	./stringconv data/strings/achievement.csv "STRN/AVM/" "avm" $(ACHIEVEMENT_LEN)
	./stringconv data/strings/badgename.csv "STRN/BDG/" "bdg" $(BADGENAME_LEN)
	./stringconv data/strings/ribbonnames.csv "STRN/RBN/" "rbn" $(RIBBONNAME_LEN)
	./stringconv data/strings/ribbondscr.csv "STRN/RBN/" "rbd" $(RIBBONDSCR_LEN)
	./stringconv data/strings/mapstring.csv "STRN/MAP/" "map" $(MAPSTRING_LEN)
	./stringconv data/strings/mysterygift.csv "STRN/UIS/" "mys" $(MGSTRING_LEN)
	./stringconv data/strings/pkmnphrases.csv "STRN/PHR/" "phr" $(PKMNPHRS_LEN)
	./stringconv data/strings/bftrainername.csv "STRN/TRN/" "bfname" $(TRNNAME_LEN)
	./stringconv data/strings/trainername.csv "STRN/TRN/" "name" $(TRNNAME_LEN)
	./stringconv data/strings/trainerintromessage.csv "STRN/TRN/" "msg1" $(TRNMSG_LEN)
	./stringconv data/strings/trainerlostmessage.csv "STRN/TRN/" "msg2" $(TRNMSG_LEN)
	./stringconv data/strings/trainerwonmessage.csv "STRN/TRN/" "msg3" $(TRNMSG_LEN)
	./stringconv data/strings/tradestr.csv "STRN/TRD/" "str" $(PKMNNAME_LEN)
	./easyChat data/easychat_word.csv "STRN/EAS/" "easw" "easyChatWordCategories.h" "EASYW_" $(EASYWORD_LEN)
	./easyChat data/easychat_phrase.csv "STRN/EAS/" "easp" "easyChatPhraseCategories.h" "EASYP_" $(EASYPHRS_LEN)
	@$(foreach tdata,$(TRAINERDATA_FILES),./trainerdata data/pkmnnames.csv data/abtynames.csv \
		data/movenames.csv data/itemnames.csv data/trainerclassnames.csv $(tdata);)
	@$(foreach mdata,$(MAPDATA_FILES),./mapdata data/pkmnnames.csv data/itemnames.csv \
		data/locationnames.csv $(mdata);)
	cp $(OUT)/bgmNames.h $(SOURCES)/bgmNames.h
	@$(foreach mscr,$(MAPSCRIPT_FILES),$(CC) -E -P -I$(SOURCES) -I$(OUT) $(mscr) | m4 > $(mscr).script; ./mapscript $(mscr).script;)
	touch fsdata

mapscript: $(OFILES) $(BUILD)/mapscript.o
	$(CC) $(LDFLAGS) -o $@ $^

pkmndata: $(OFILES) $(BUILD)/pkmndata.o
	$(CC) $(LDFLAGS) -o $@ $^

locationdata: $(OFILES) $(BUILD)/locationdata.o
	$(CC) $(LDFLAGS) -o $@ $^

trainerdata: $(OFILES) $(BUILD)/trainerdata.o
	$(CC) $(LDFLAGS) -o $@ $^

mapdata: $(OFILES) $(BUILD)/mapdata.o
	$(CC) $(LDFLAGS) -o $@ $^

stringconv: $(OFILES) $(BUILD)/stringconv.o
	$(CC) $(LDFLAGS) -o $@ $^

easyChat: $(OFILES) $(BUILD)/easyChat.o
	$(CC) $(LDFLAGS) -o $@ $^

battleFrontier: $(OFILES) $(BUILD)/battleFrontier.o
	$(CC) $(LDFLAGS) -o $@ $^

battleFrontierTrainer: $(OFILES) $(BUILD)/battleFrontierTrainer.o
	$(CC) $(LDFLAGS) -o $@ $^

wonderCard: $(OFILES) $(BUILD)/wonderCard.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	@rm -r $(BUILD)
	@rm fsdata
	@rm locationdata
	@rm pkmndata
	@rm mapdata
	@rm strings
	@rm easychat
	@rm battlerFrontier
	@rm battlerFrontierTrainer

$(BUILD)/%.o: $(SOURCES)/%.cpp
	@mkdir -p $(BUILD)
	$(CC) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/%.o: $(SOURCES)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJFILES:.o=.d)

