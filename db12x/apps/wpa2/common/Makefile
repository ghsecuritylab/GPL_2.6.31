# common/Makefile -- common code shared by wpa_supplicant and hostapd
# These were extracted from the original distribution and placed here
# in order to be able to make a shared library.

# Change the following to switch configurations:
include full.config

include Makefile.common

# wpa_common is shared library between hostapd and wpa_supplicant programs
# wpa_ctrl is shared library for talking to hostapd or wpa_supplicant
ifeq ($(BUILD_WPA2_STATIC_COMMON_LIBRARY),y)
ALL=libwpa_common.a libwpa_ctrl.a libwpa_ctrl.so
else
ALL=libwpa_common.a libwpa_common.so libwpa_ctrl.a libwpa_ctrl.so
#ALL=libwpa_common.so libwpa_ctrl.so
endif

all: $(ALL)
	echo DID all common code ok.

install: all
	cp -a $(ALL) $(INSTALL_ROOT)/lib/.

###### Should not hurt to always compile the following?
OBJS = 
OBJS += common.o
OBJS += rc4.o
## OBJS += md4.o sha1.o des.o
OBJS += configedit.o
OBJS += fileutil.o

###### Operating system shim layer os_
OBJS += os_$(CONFIG_OS).o

####### eloop -- callback manager
OBJS += $(CONFIG_ELOOP).o

######################
ifdef CONFIG_IAPP
OBJS += iapp.o
endif

#############
#ifdef CONFIG_RSN_PREAUTH
#endif


####### l2 packet -- packet injection / capture
#ifndef CONFIG_L2_PACKET
#endif
OBJS += l2_packet_$(CONFIG_L2_PACKET).o
ifeq ($(CONFIG_L2_PACKET), freebsd)
OBJS += l2_packet_freebsd.o
endif

################
ifdef CONFIG_EAP_TLS
OBJS += eap_tls.o
endif

#################
#ifdef CONFIG_EAP_PEAP
#endif

##################
ifdef CONFIG_EAP_TTLS
endif

#################
ifdef CONFIG_EAP_MD5
endif

################
ifdef CONFIG_EAP_MSCHAPV2
endif

#################
ifdef CONFIG_EAP_GTC
endif

#################
ifdef CONFIG_EAP_OTP
endif

##############
ifdef CONFIG_EAP_SIM
endif

############
ifdef CONFIG_EAP_LEAP
endif

################
ifdef CONFIG_EAP_PSK
OBJS += eap_psk_common.o
endif

##############
ifdef CONFIG_EAP_AKA
endif

##############
ifdef CONFIG_EAP_SIM_COMMON
OBJS += eap_sim_common.o
endif
CFLAGS += -fPIC
############
ifdef CONFIG_EAP_TLV
CFLAGS += -DEAP_TLV
endif

####################
ifdef CONFIG_EAP_FAST
endif

#########
ifdef CONFIG_EAP_PAX
OBJS += eap_pax_common.o
endif

###########
ifdef CONFIG_EAP_SAKE
OBJS += eap_sake_common.o
endif

############
ifdef CONFIG_EAP_GPSK
OBJS += eap_gpsk_common.o
endif

##############
ifdef CONFIG_EAP_WPS
OBJS += wps_parser.o
ifeq ($(CONFIG_WPS_OPT_UPNP),y)
ifeq ($(CONFIG_TINYUPNP),y)
else
OBJS += upnp_wps_common.o
endif
endif
endif #CONFIG_EAP_WPS

###########
ifdef CONFIG_IEEE8021X_EAPOL
# IEEE 802.1X/EAPOL state machines (e.g., for RADIUS authentication)
endif

#############
ifdef CONFIG_PCSC
endif

##########################
ifdef CONFIG_EAP
endif

#######################
ifndef CONFIG_TLS
endif

##################
ifdef TLS_FUNCS
# Shared TLS functions (needed for EAP_TLS, EAP_PEAP, EAP_TTLS, and EAP_FAST)
# OBJS += eap_tls_common.o
ifeq ($(CONFIG_TLS), openssl)
OBJS += tls_openssl.o
endif   # openssl
ifeq ($(CONFIG_TLS), gnutls)
OBJS += tls_gnutls.o
ifdef CONFIG_GNUTLS_EXTRA
endif  # CONFIG_GNUTLS_EXTRA
endif  # gnutls
ifeq ($(CONFIG_TLS), schannel)
OBJS += tls_schannel.o
endif  # schannel
ifeq ($(CONFIG_TLS), internal)
OBJS += tls_internal.o tlsv1_common.o tlsv1_client.o x509v3.o
#should be# OBJS += asn1.o
ifneq ($(CONFIG_BACKEND), file)
OBJS += base64.o
endif  # file
ifeq ($(CONFIG_CRYPTO), internal)
ifdef CONFIG_INTERNAL_LIBTOMMATH
else  # CONFIG_CRYPTO internal
endif # CONFIG_CRYPTO internal
endif # CRYPTO internal
ifeq ($(CONFIG_CRYPTO), libtomcrypt)
endif # CRYPTO libtomcrypt
endif # CONFIG_TLS internal
ifeq ($(CONFIG_TLS), none)
OBJS += tls_none.o
endif # CONFIG_TLS none
ifdef CONFIG_SMARTCARD
ifndef CONFIG_NATIVE_WINDOWS
ifneq ($(CONFIG_L2_PACKET), freebsd)
endif # CONFIG_L2_PACKET freebsd
endif # CONFIG_NATIVE_WINDOWS
endif # CONFIG_SMARTCARD
NEED_CRYPTO=y
else  # TLS_FUNCS
OBJS += tls_none.o
endif # TLS_FUNCS


############
ifdef CONFIG_PKCS12
endif

###########
ifdef CONFIG_SMARTCARD
endif

##########
#always# ifdef MS_FUNCS
OBJS += ms_funcs.o
#always# endif

###############
ifdef NEED_CRYPTO
ifndef TLS_FUNCS
ifeq ($(CONFIG_TLS), openssl)
endif
ifeq ($(CONFIG_TLS), gnutls)
endif
ifeq ($(CONFIG_TLS), schannel)
endif
ifeq ($(CONFIG_TLS), internal)
ifeq ($(CONFIG_CRYPTO), libtomcrypt)
endif
endif
endif
ifeq ($(CONFIG_TLS), openssl)
OBJS += crypto.o
endif
ifeq ($(CONFIG_TLS), gnutls)
OBJS += crypto_gnutls.o
endif
ifeq ($(CONFIG_TLS), schannel)
OBJS += crypto_cryptoapi.o
endif
ifeq ($(CONFIG_TLS), internal)
ifeq ($(CONFIG_CRYPTO), libtomcrypt)
OBJS += crypto_libtomcrypt.o
endif

ifeq ($(CONFIG_CRYPTO), internal)
OBJS += crypto_internal.o
OBJS += bignum.o
OBJS += rsa.o
OBJS += des.o
OBJS += asn1.o
endif

########## Crypto math
ifeq ($(CONFIG_CRYPTO), cryptoapi)
OBJS += crypto_cryptoapi.o
endif
endif
ifeq ($(CONFIG_TLS), none)
OBJS += crypto_none.o
endif
else
endif

############
ifdef CONFIG_INTERNAL_AES
endif
ifdef CONFIG_INTERNAL_SHA1
OBJS += sha1.o
endif
ifdef CONFIG_INTERNAL_SHA256
endif
ifdef CONFIG_INTERNAL_MD5
OBJS += md5.o
endif
ifdef CONFIG_INTERNAL_MD4
OBJS += md4.o
endif
ifdef CONFIG_INTERNAL_DES
endif

ifdef CONFIG_RADIUS_SERVER
OBJS += radius_server.o
endif

#############
ifdef NEED_SHA256
OBJS += sha256.o
endif

#### control interface
ifdef CONFIG_CTRL_IFACE
ifeq ($(CONFIG_CTRL_IFACE), y)
ifdef CONFIG_NATIVE_WINDOWS
else
endif
endif
ifeq ($(CONFIG_CTRL_IFACE), unix)
endif
ifeq ($(CONFIG_CTRL_IFACE), udp)
endif
ifeq ($(CONFIG_CTRL_IFACE), named_pipe)
endif
endif
ifdef CONFIG_CTRL_IFACE_DBUS
OBJS += ctrl_iface_dbus.o ctrl_iface_dbus_handlers.o dbus_dict_helpers.o
endif

#################
ifdef NEED_HTTPREAD
OBJS += httpread.o
endif

####### Debugging messages
ifdef CONFIG_NO_STDOUT_DEBUG
ifndef CONFIG_CTRL_IFACE
endif
endif

##############
ifdef CONFIG_PEERKEY
endif

############
ifdef CONFIG_IEEE80211W
endif

################
ifndef CONFIG_NO_WPA
else
endif

###############
ifdef CONFIG_NO_WPA2
endif

################
ifdef CONFIG_NO_AES_EXTRAS
endif

#############
ifdef NEED_AES
OBJS += aes_wrap.o
endif

###########
ifdef CONFIG_CLIENT_MLME
endif

#############
ifndef CONFIG_MAIN
endif

libwpa_common.a : $(OBJS)
	rm -f libwpa_common.a
	$(AR) rcs libwpa_common.a $(OBJS)

ifeq ($(BUILD_WPA2_STATIC_COMMON_LIBRARY),y)
else
libwpa_common.so : $(OBJS)
	rm -f libwpa_common.so
	$(CC) -shared -o libwpa_common.so $(OBJS)
endif


OBJS_wpa_ctrl = wpa_ctrl.o
OBJS_wpa_ctrl += os_$(CONFIG_OS).o

libwpa_ctrl.a : $(OBJS_wpa_ctrl)
	rm -f libwpa_ctrl.a
	$(AR) rcs libwpa_ctrl.a $(OBJS_wpa_ctrl)

libwpa_ctrl.so : $(OBJS_wpa_ctrl)
	rm -f libwpa_ctrl.so
	$(CC) -shared -o libwpa_ctrl.so $(OBJS_wpa_ctrl)

clean:
	rm -f core junk* *~ *.o *.d *.a *.so $(ALL) $(WINALL)

-include $(OBJS:%.o=%.d)
-include $(OBJS_wpa_ctrl:%.o=%.d)

