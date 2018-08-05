/*
   Copyright (c) 2016, The CyanogenMod Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fcntl.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm8937.h"

using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[],
    char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void check_boardinfo()
{
	char board_id[15];
	FILE *lenovo_id;
	lenovo_id = fopen ("/sys/devices/soc0/platform_lenovo_hardware_type", "r");
	fscanf(lenovo_id, "%s" , board_id);
	fclose (lenovo_id);

        if (strcmp(board_id, "S82939AA1") == 0) {
		property_override("ro.build.product", "K53a48");
		property_override("ro.product.board", "S82939AA1");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "K53a48");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo K53a48");
		property_set("persist.radio.multisim.config", "dsds");
		property_set("ro.telephony.default_network", "9,9");
	}
        else if (strcmp(board_id, "S82939BA1") == 0) {
		property_override("ro.build.product", "K53a48");
		property_override("ro.product.board", "S82939BA1");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "K53a48");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo K53a48");
		property_set("persist.radio.multisim.config", "dsds");
		property_set("ro.telephony.default_network", "9,9");
	}
        else if (strcmp(board_id, "S82939CA1") == 0) {
		property_override("ro.build.product", "K53a48");
		property_override("ro.product.board", "S82939CA1");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "K53a48");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo K53a48");
		property_set("ro.telephony.default_network", "9");
	}
        else if (strcmp(board_id, "S82939FA1") == 0) {
		property_override("ro.build.product", "K53b36");
		property_override("ro.product.board", "S82939FA1");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "K53b36");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo K53b36");
		property_set("persist.radio.multisim.config", "dsds");
		property_set("ro.telephony.default_network", "9,9");
	}
        else {
		property_override("ro.product.board", "S82939GA1");
		property_override_dual("ro.product.device", "ro.vendor.product.device", "K53b37");
		property_override_dual("ro.product.model", "ro.vendor.product.model", "Lenovo K53b37");
		property_override("ro.build.product", "K53b37");
		property_set("ro.telephony.default_network", "9");
	}
}

void init_target_properties()
{
    check_boardinfo();
}
