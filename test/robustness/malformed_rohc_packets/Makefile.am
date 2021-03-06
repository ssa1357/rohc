################################################################################
#	Name       : Makefile
#	Author     : Didier Barvaux <didier@barvaux.org>
#	Description: create the test tool that checks that decompression of malformed
#	             ROHC packets fails without crashing
################################################################################


TESTS = \
	test_malformed_rohc_packets_ir_1.sh \
	test_malformed_rohc_packets_ir_with_list_encoding_type1_1.sh \
	test_malformed_rohc_packets_truncated_uor2id_14.sh \
	test_malformed_rohc_packets_large_feedback_3.sh \
	test_malformed_rohc_packets_tcp_ir_01_1.sh \
	test_malformed_rohc_packets_tcp_ir_02_1.sh \
	test_malformed_rohc_packets_tcp_ir_03_1.sh \
	test_malformed_rohc_packets_tcp_ir_04_1.sh \
	test_malformed_rohc_packets_tcp_ir_05_1.sh \
	test_malformed_rohc_packets_tcp_ir_06_1.sh \
	test_malformed_rohc_packets_tcp_ir_07_1.sh \
	test_malformed_rohc_packets_tcp_ir_08_1.sh \
	test_malformed_rohc_packets_tcp_ir_09_1.sh \
	test_malformed_rohc_packets_tcp_ir_10_1.sh \
	test_malformed_rohc_packets_tcp_ir_11_1.sh \
	test_malformed_rohc_packets_tcp_ir_12_1.sh \
	test_malformed_rohc_packets_tcp_ir_13_1.sh \
	test_malformed_rohc_packets_tcp_ir_14_1.sh \
	test_malformed_rohc_packets_tcp_ir_15_1.sh \
	test_malformed_rohc_packets_tcp_ir_16_1.sh \
	test_malformed_rohc_packets_tcp_ir_17_1.sh \
	test_malformed_rohc_packets_tcp_ir_18_1.sh \
	test_malformed_rohc_packets_tcp_ir_19_1.sh \
	test_malformed_rohc_packets_tcp_ir_20_1.sh \
	test_malformed_rohc_packets_tcp_ir_21_1.sh \
	test_malformed_rohc_packets_tcp_ir_22_1.sh \
	test_malformed_rohc_packets_tcp_ir_23_1.sh \
	test_malformed_rohc_packets_tcp_ir_24_1.sh \
	test_malformed_rohc_packets_tcp_ir_25_1.sh \
	test_malformed_rohc_packets_tcp_ir_26_1.sh \
	test_malformed_rohc_packets_uo0_no_context_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_331_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_410_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_916_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_1200_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_1229_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_1308_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_1749_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_2723_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_27946_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_2887_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_2961_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_3013_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_3255_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_3455_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_3612_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_3854_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4271_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4363_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4480_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4570_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4762_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4866_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4927_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4934_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_4963_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_5632_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28005_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28006_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28007_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28008_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28456_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28457_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28459_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28460_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28464_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28580_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28743_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28753_1.sh \
	test_malformed_rohc_packets_fuzzer_crash_28799_1.sh \
	test_malformed_rohc_packets_afl00_from_1_to_2_ip_headers_0.sh \
	test_malformed_rohc_packets_afl01_tcp_seq_scaled_not_initialized_0.sh \
	test_malformed_rohc_packets_afl02_rtp_profile_ir_without_dynamic_chain_0.sh \
	test_malformed_rohc_packets_afl03_from_1_to_2_ip_headers_other_0.sh \
	test_malformed_rohc_packets_afl04_from_1_to_2_ip_headers_other_0.sh \
	test_malformed_rohc_packets_afl05_malformed_feedback_header_0.sh \
	test_malformed_rohc_packets_afl06_from_ipv6_to_ipv4_0.sh \
	test_malformed_rohc_packets_afl07_short_irregular_chain_0.sh \
	test_malformed_rohc_packets_afl08_rtp_profile_ir_without_dynamic_chain_sn_0xffff_0.sh \
	test_malformed_rohc_packets_afl09_rtp_uor2ts_ext3_too_short_0.sh \
	test_malformed_rohc_packets_afl10_uncompressed_irdyn_feedback_0.sh \
	test_malformed_rohc_packets_afl11_unknown_packet_type_0.sh \
	test_malformed_rohc_packets_afl12_largecid_ipv6_ext_list_malformed_ins_mask_0.sh \
	test_malformed_rohc_packets_afl13_largecid_tcp_options_not_multiple_32bit_words_0.sh \
	test_malformed_rohc_packets_afl14_largecid_tcp_options_too_long_0.sh \
	test_malformed_rohc_packets_tcp_context_replication_bad_base_cid_0.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_01_1.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_02_1.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_03_1.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_04_1.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_05_178.sh \
	test_malformed_rohc_packets_rohcv2_ip_ir_06_178.sh \
	test_truncated_packets_rohc_mc0_wlsb4_smallcid.sh \
	test_truncated_packets_rohc_mc0_wlsb64_smallcid.sh \
	test_truncated_packets_rohc_mc1_wlsb4_smallcid.sh \
	test_truncated_packets_rohc_mc1_wlsb64_smallcid.sh \
	test_truncated_packets_rohc_mc0_wlsb4_largecid.sh \
	test_truncated_packets_rohc_mc0_wlsb64_largecid.sh \
	test_truncated_packets_rohc_mc1_wlsb4_largecid.sh \
	test_truncated_packets_rohc_mc1_wlsb64_largecid.sh \
	test_truncated_packets_rohcv2_mc0_wlsb4_smallcid.sh \
	test_truncated_packets_rohcv2_mc1_wlsb4_smallcid.sh \
	test_truncated_packets_rohcv2_mc1_wlsb64_smallcid.sh \
	test_truncated_packets_rohcv2_mc0_wlsb64_smallcid.sh \
	test_truncated_packets_rohcv2_mc0_wlsb4_largecid.sh \
	test_truncated_packets_rohcv2_mc0_wlsb64_largecid.sh \
	test_truncated_packets_rohcv2_mc1_wlsb4_largecid.sh \
	test_truncated_packets_rohcv2_mc1_wlsb64_largecid.sh


check_PROGRAMS = \
	test_malformed_rohc_packets


test_malformed_rohc_packets_CFLAGS = \
	$(configure_cflags) \
	-Wno-unused-parameter \
	-Wno-sign-compare

test_malformed_rohc_packets_CPPFLAGS = \
	-I$(top_srcdir)/test \
	-I$(top_srcdir)/src/common \
	-I$(top_srcdir)/src/comp \
	-I$(top_srcdir)/src/decomp \
	$(libpcap_includes)

test_malformed_rohc_packets_LDFLAGS = \
	$(configure_ldflags)

test_malformed_rohc_packets_SOURCES = \
	test_malformed_rohc_packets.c

test_malformed_rohc_packets_LDADD = \
	-l$(pcap_lib_name) \
	$(top_builddir)/src/librohc.la \
	$(additional_platform_libs)

EXTRA_DIST = \
	test_malformed_rohc_packets.sh \
	test_truncated_packets.sh \
	$(TESTS) \
	inputs

