# party files are run through trainerproc, which is a tool that converts party data to an output file
# matching the current trainer .h formatting

AUTO_GEN_TARGETS += src/data/trainers.h
AUTO_GEN_TARGETS += src/data/trainers_frlg.h
AUTO_GEN_TARGETS += src/data/battle_partners.h
AUTO_GEN_TARGETS += test/battle/trainer_control.h
AUTO_GEN_TARGETS += test/battle/partner_control.h
AUTO_GEN_TARGETS += src/data/debug_trainers.h

# Generated headers are shared between build directories. Invalidate them when
# preprocessing changes, including switching from the original game to the demo.
.PHONY: force-trainer-config
force-trainer-config:

$(BUILD_DIR)/trainer-config.txt: force-trainer-config
	@mkdir -p $(BUILD_DIR)
	@printf '%s\n' '$(CPPFLAGS)' > $@.tmp
	@cmp -s $@.tmp $@ || cp $@.tmp $@
	@rm -f $@.tmp

%.h: %.party $(TRAINERPROC) $(BUILD_DIR)/trainer-config.txt
	$(CPP) $(CPPFLAGS) -traditional-cpp - < $< | $(TRAINERPROC) -o $@ -i $< -
