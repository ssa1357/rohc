/*
 * Copyright 2010,2011,2012,2013,2014 Didier Barvaux
 * Copyright 2007,2008 Thales Alenia Space
 * Copyright 2007,2008,2009,2010,2012,2014 Viveris Technologies
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
 * @file   rohc_comp_rfc3095.h
 * @brief  Generic framework for RFC3095-based compression profiles such as
 *         IP-only, UDP, UDP-Lite, ESP, and RTP profiles.
 * @author Didier Barvaux <didier.barvaux@toulouse.viveris.com>
 * @author Didier Barvaux <didier@barvaux.org>
 */

#ifndef ROHC_COMP_RFC3095_H
#define ROHC_COMP_RFC3095_H

#include "rohc_comp_internals.h"
#include "rohc_packets.h"
#include "protocols/uncomp_pkt_hdrs.h"
#include "schemes/comp_list.h"
#include "ip.h"
#include "crc.h"

#include <stdlib.h>


/**
 * @brief Store information about an IPv4 header between the different
 *        compressions of IP packets.
 *
 * Defines an object that contains counters, flags and structures related to an
 * IPv4 header and that need to be saved between the different compressions of
 * packets. A compression context owns objects like this for the two first
 * IPv4 headers.
 */
struct ipv4_header_info
{
	/// A window to store the IP-ID
	struct c_wlsb ip_id_window;

	/// The previous IP header
	struct ipv4_hdr old_ip;

	/// The number of times the DF field was added to the compressed header
	uint8_t df_count;
	/// @brief The number of times the IP-ID is specified as random in the
	///        compressed header
	uint8_t rnd_count;
	/// @brief The number of times the IP-ID is specified as coded in Network
	///        Byte Order (NBO) in the compressed header
	uint8_t nbo_count;
	/// @brief The number of times the IP-ID is specified as static in the
	///        compressed header
	uint8_t sid_count;

	/// Whether the IP-ID is considered as random or not
	int rnd;
	/// Whether the IP-ID is considered as coded in NBO or not
	int nbo;
	/// Whether the IP-ID is considered as static or not
	int sid;
	/// @brief Whether the IP-ID of the previous IP header was considered as
	///        random or not
	int old_rnd;
	/// @brief Whether the IP-ID of the previous IP header was considered as
	///        coded in NBO or not
	int old_nbo;
	/// @brief Whether the IP-ID of the previous IP header was considered as
	///        static or not
	int old_sid;

	/// The delta between the IP-ID and the current Sequence Number (SN)
	/// (overflow over 16 bits is expected when SN > IP-ID)
	uint16_t id_delta;
};


/**
 * @brief Store information about an IPv6 header between the different
 *        compressions of IP packets.
 *
 * Defines an object that contains counters, flags and structures related to an
 * IPv6 header and that need to be saved between the different compressions of
 * packets. A compression context owns objects like this for the two first
 * IPv6 headers.
 */
struct ipv6_header_info
{
	/// The previous IPv6 header
	struct ipv6_hdr old_ip;
	/// The extension compressor
	struct list_comp ext_comp;
};


/**
 * @brief Store information about an IP (IPv4 or IPv6) header between the
 *        different compressions of IP packets.
 */
struct ip_header_info
{
	ip_version version;            ///< The version of the IP header
	bool static_chain_end;

	/// The number of times the TOS/TC field was added to the compressed header
	size_t tos_count;
	/// The number of times the TTL/HL field was added to the compressed header
	size_t ttl_count;

	/** Whether the old_* members of the struct and in its children are
	 *  initialized or not */
	bool is_first_header;

	union
	{
		struct ipv4_header_info v4; ///< The IPv4-specific header info
		struct ipv6_header_info v6; ///< The IPv6-specific header info
	} info;                        ///< The version specific header info
};


/** The changes of one IP header */
struct rfc3095_ip_hdr_changes
{
	uint8_t tos_tc_just_changed:1; /**< Whether IP TOS/TC just changed */
	uint8_t tos_tc_changed:1;      /**< Whether IP TOS/TC changed */
	uint8_t ttl_hl_just_changed:1; /**< Whether IP TTL/HL just changed */
	uint8_t ttl_hl_changed:1;      /**< Whether IP TTL/HL changed */
	uint8_t df_just_changed:1;     /**< Whether IP DF just changed */
	uint8_t df_changed:1;          /**< Whether IP DF changed */
	uint8_t nbo_just_changed:1;    /**< Whether IP NBO just changed */
	uint8_t nbo_changed:1;         /**< Whether IP NBO changed */

	uint8_t rnd_just_changed:1;    /**< Whether IP RND just changed */
	uint8_t rnd_changed:1;         /**< Whether IP RND changed */
	uint8_t sid_just_changed:1;    /**< Whether IP SID just changed */
	uint8_t sid_changed:1;         /**< Whether IP SID changed */
	uint8_t ip_id_changed:1;         /**< Whether IP-ID of the IP header changed */
	uint8_t ip_id_3bits_possible:1;  /**< Whether IP-ID may be encoded on 3 bits */
	uint8_t ip_id_5bits_possible:1;  /**< Whether IP-ID may be encoded on 5 bits */
	uint8_t ip_id_6bits_possible:1;  /**< Whether IP-ID may be encoded on 6 bits */

	uint8_t ip_id_8bits_possible:1;  /**< Whether IP-ID may be encoded on 8 bits */
	uint8_t ip_id_11bits_possible:1; /**< Whether IP-ID may be encoded on 11 bits */
	/** Whether innermost IP extension list just changed of structure */
	uint8_t ext_list_struct_just_changed:1;
	/** Whether innermost IP extension list changed of structure */
	uint8_t ext_list_struct_changed:1;
	/** Whether innermost IP extension list just changed of content */
	uint8_t ext_list_content_just_changed:1;
	/** Whether innermost IP extension list changed of content */
	uint8_t ext_list_content_changed:1;
	uint8_t unused:2;
};


/** The temporary variables for RFC3095-based profiles
 *
 * Structure that contains variables that are temporary, i.e. variables that
 * will only be used for the compression of the current packet. These variables
 * must be reinitialized every time a new packet arrive.
 *
 * @see c_init_tmp_variables
 */
struct rfc3095_tmp_state
{
	/** The number of IP headers */
	size_t ip_hdr_nr;
	/** The changes of the IP headers */
	struct rfc3095_ip_hdr_changes ip_hdr_changes[ROHC_MAX_IP_HDRS];

	bool sn_4bits_possible;
	bool sn_7bits_possible;
	bool sn_12bits_possible;

	bool sn_5bits_possible;
	bool sn_8bits_possible;
	bool sn_13bits_possible;

	bool sn_6bits_possible;
	bool sn_9bits_possible;
	bool sn_14bits_possible;

	/** Whether the UDP checksum changed of behavior with the current packet */
	uint16_t udp_check_behavior_just_changed:1;
	/** Whether the UDP checksum changed of behavior with the last few packets */
	uint16_t udp_check_behavior_changed:1;
	/** Whether the RTP Version changed with the current packet */
	uint16_t rtp_version_just_changed:1;
	/** Whether the RTP Version changed with the last few packets */
	uint16_t rtp_version_changed:1;
	/** Whether the RTP Padding (P) bit changed with the current packet */
	uint16_t rtp_padding_just_changed:1;
	/** Whether the RTP Padding (P) bit changed with the last few packets */
	uint16_t rtp_padding_changed:1;
	/** Whether the RTP eXtension (X) bit changed with the current packet */
	uint16_t rtp_ext_just_changed:1;
	/** Whether the RTP eXtension (X) bit changed with the last few packets */
	uint16_t rtp_ext_changed:1;
	uint16_t is_marker_bit_set:1;   /**< Whether RTP Marker (M) bit is set */
	/** Whether the RTP Payload Type (PT) changed with the current packet */
	uint16_t rtp_pt_just_changed:1;
	/** Whether the RTP Payload Type (PT) changed with the last few packets */
	uint16_t rtp_pt_changed:1;
	uint16_t unused:5;

	/** The TS field to send (ts_scaled or ts) */
	uint32_t ts_send;
	/** The number of bits needed to encode ts_send */
	uint8_t nr_ts_bits;
	/** The number of bits of TS to place in the extension 3 header */
	uint8_t nr_ts_bits_ext3;
};


/**
 * @brief The generic decompression context for RFC3095-based profiles
 *
 * The object defines the generic context that manages IP(/nextheader) and
 * IP/IP(/nextheader) packets. nextheader is managed by the profile-specific
 * part of the context.
 */
struct rohc_comp_rfc3095_ctxt
{
	/// The Sequence Number (SN), may be 16-bit or 32-bit long
	uint32_t sn;
	/// A window used to encode the SN
	struct c_wlsb sn_window;

	/** The SN of the last packet that updated the context (used to determine
	 * if a positive ACK may cause a transition to a higher compression state) */
	uint32_t msn_of_last_ctxt_updating_pkt;
	/** The W-LSB for non-acknowledged MSN */
	struct c_wlsb msn_non_acked;

	/** The number of IP headers */
	size_t ip_hdr_nr;
	/** Information about the IP headers */
	struct ip_header_info ip_ctxts[ROHC_MAX_IP_HDRS];

	/** Whether the cache for the CRC-3 value on CRC-STATIC fields is initialized or not */
	bool is_crc_static_3_cached_valid;
	/** The cache for the CRC-3 value on CRC-STATIC fields */
	uint8_t crc_static_3_cached;
	/** Whether the cache for the CRC-7 value on CRC-STATIC fields is initialized or not */
	bool is_crc_static_7_cached_valid;
	/** The cache for the CRC-7 value on CRC-STATIC fields */
	uint8_t crc_static_7_cached;

	/// Temporary variables that are used during one single compression of packet
	struct rfc3095_tmp_state tmp;

	/* below are some information and handlers to manage the next header
	 * (if any) located just after the IP headers (1 or 2 IP headers) */

	/// The protocol number registered by IANA for the next header protocol
	unsigned int next_header_proto;
	/// The length of the next header
	unsigned int next_header_len;

	/** The handler for encoding profile-specific uncompressed header fields */
	void (*encode_uncomp_fields)(struct rohc_comp_ctxt *const context,
	                             const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs)
		__attribute__((nonnull(1, 2)));

	/** @brief The handler used to decide which packet to send in FO state */
	rohc_packet_t (*decide_FO_packet)(const struct rohc_comp_ctxt *const context)
		__attribute__((warn_unused_result, nonnull(1)));
	/** @brief The handler used to decide which packet to send in SO state */
	rohc_packet_t (*decide_SO_packet)(const struct rohc_comp_ctxt *const context)
		__attribute__((warn_unused_result, nonnull(1)));
	/** The handler used to decide which extension to send */
	rohc_ext_t (*decide_extension)(const struct rohc_comp_ctxt *const context,
	                               const rohc_packet_t packet_type)
		__attribute__((warn_unused_result, nonnull(1)));

	/** Determine the next SN value */
	uint32_t (*get_next_sn)(const struct rohc_comp_ctxt *const context,
	                        const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs)
		__attribute__((warn_unused_result, nonnull(1, 2)));

	/// @brief The handler used to add the static part of the next header to the
	///        ROHC packet
	size_t (*code_static_part)(const struct rohc_comp_ctxt *const context,
	                           const uint8_t *const next_header,
	                           uint8_t *const dest,
	                           const size_t counter)
		__attribute__((warn_unused_result, nonnull(1, 2, 3)));

	/// @brief The handler used to add the dynamic part of the next header to the
	///        ROHC pachet
	size_t (*code_dynamic_part)(const struct rohc_comp_ctxt *const context,
	                            const uint8_t *const next_header,
	                            uint8_t *const dest,
	                            const size_t counter)
		__attribute__((warn_unused_result, nonnull(1, 2, 3)));

	/// @brief The handler used to add the IR/IR-DYN remainder header to the
	///        ROHC pachet
	int (*code_ir_remainder)(const struct rohc_comp_ctxt *const context,
	                         uint8_t *const dest,
	                         const size_t dest_max_len,
	                         const size_t counter)
		__attribute__((warn_unused_result, nonnull(1, 2)));

	/// @brief The handler used to add an additional header in the tail of the
	///        UO-0, UO-1 and UO-2 packets
	size_t (*code_uo_remainder)(const struct rohc_comp_ctxt *const context,
	                            const uint8_t *const next_header,
	                            uint8_t *const dest,
	                            const size_t counter)
		__attribute__((warn_unused_result, nonnull(1, 2, 3)));

	/// @brief The handler used to compute the CRC-STATIC value
	uint8_t (*compute_crc_static)(const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs,
	                              const rohc_crc_type_t crc_type,
	                              const uint8_t init_val)
		__attribute__((nonnull(1), warn_unused_result));

	/// @brief The handler used to compute the CRC-DYNAMIC value
	uint8_t (*compute_crc_dynamic)(const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs,
	                               const rohc_crc_type_t crc_type,
	                               const uint8_t init_val)
		__attribute__((nonnull(1), warn_unused_result));

	/// Profile-specific data
	void *specific;
};


/*
 * Function prototypes.
 */

bool rohc_comp_rfc3095_create(struct rohc_comp_ctxt *const context,
                              const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs)
	__attribute__((warn_unused_result, nonnull(1, 2)));

void rohc_comp_rfc3095_destroy(struct rohc_comp_ctxt *const context)
	__attribute__((nonnull(1)));

rohc_ext_t decide_extension(const struct rohc_comp_ctxt *const context,
                            const rohc_packet_t packet_type)
	__attribute__((warn_unused_result, nonnull(1)));

int rohc_comp_rfc3095_encode(struct rohc_comp_ctxt *const context,
                             const struct rohc_pkt_hdrs *const uncomp_pkt_hdrs,
                             uint8_t *const rohc_pkt,
                             const size_t rohc_pkt_max_len,
                             rohc_packet_t *const packet_type)
	__attribute__((warn_unused_result, nonnull(1, 2, 3, 5)));

bool rohc_comp_rfc3095_feedback(struct rohc_comp_ctxt *const context,
                                const enum rohc_feedback_type feedback_type,
                                const uint8_t *const packet,
                                const size_t packet_len,
                                const uint8_t *const feedback_data,
                                const size_t feedback_data_len)
	__attribute__((warn_unused_result, nonnull(1, 3, 5)));

void rohc_get_ipid_bits(const struct rohc_comp_ctxt *const context,
                        bool *const innermost_ip_id_changed,
                        bool *const innermost_ip_id_3bits_possible,
                        bool *const innermost_ip_id_5bits_possible,
                        bool *const innermost_ip_id_8bits_possible,
                        bool *const innermost_ip_id_11bits_possible,
                        bool *const outermost_ip_id_changed,
                        bool *const outermost_ip_id_11bits_possible)
	__attribute__((nonnull(1, 2, 3, 4, 5, 6, 7, 8)));


/**
 * @brief How many IP headers are IPv4 headers with non-random IP-IDs ?
 *
 * @param ctxt  The generic decompression context
 * @return      The number of IPv4 headers with non-random IP-ID fields
 */
static inline size_t get_nr_ipv4_non_rnd(const struct rohc_comp_rfc3095_ctxt *const ctxt)
{
	size_t nr_ipv4_non_rnd = 0;
	size_t ip_hdr_pos;

	for(ip_hdr_pos = 0; ip_hdr_pos < ctxt->ip_hdr_nr; ip_hdr_pos++)
	{
		const struct ip_header_info *const ip_ctxt = &(ctxt->ip_ctxts[ip_hdr_pos]);

		if(ip_ctxt->version == IPV4 && ip_ctxt->info.v4.rnd != 1)
		{
			nr_ipv4_non_rnd++;
		}
	}

	return nr_ipv4_non_rnd;
}


/**
 * @brief How many IP headers are IPv4 headers with non-random IP-IDs and some
 *        bits to transmit ?
 *
 * @param ctxt  The generic compression context
 * @return      The number of IPv4 headers with non-random IP-ID fields and some
 *              bits to transmit
 */
static inline size_t get_nr_ipv4_non_rnd_with_bits(const struct rohc_comp_rfc3095_ctxt *const ctxt)
{
	size_t nr_ipv4_non_rnd_with_bits = 0;
	size_t ip_hdr_pos;

	for(ip_hdr_pos = 0; ip_hdr_pos < ctxt->ip_hdr_nr; ip_hdr_pos++)
	{
		const struct ip_header_info *const ip_ctxt = &(ctxt->ip_ctxts[ip_hdr_pos]);
		const struct rfc3095_ip_hdr_changes *const ip_changes =
			&(ctxt->tmp.ip_hdr_changes[ip_hdr_pos]);

		if(ip_ctxt->version == IPV4 &&
		   ip_ctxt->info.v4.rnd != 1 &&
		   ip_changes->ip_id_changed)
		{
			nr_ipv4_non_rnd_with_bits++;
		}
	}

	return nr_ipv4_non_rnd_with_bits;
}


/**
 * @brief at least one SID flag changed now or in the last few packets?
 *
 * @param ctxt               The generic compression context
 * @param oa_repetitions_nr  The number of Optimistic Approach repetitions
 * @return                   true if at least one SID flag changed now or in
 *                           last few packets, false otherwise
 */
static inline bool does_at_least_one_sid_change(const struct rohc_comp_rfc3095_ctxt *const ctxt,
                                                const uint8_t oa_repetitions_nr)
{
	bool at_least_one_sid_change = false;
	size_t ip_hdr_pos;

	for(ip_hdr_pos = 0; ip_hdr_pos < ctxt->ip_hdr_nr; ip_hdr_pos++)
	{
		const struct ip_header_info *const ip_ctxt = &(ctxt->ip_ctxts[ip_hdr_pos]);

		if(ip_ctxt->version == IPV4 && ip_ctxt->info.v4.sid_count < oa_repetitions_nr)
		{
			at_least_one_sid_change = true;
		}
	}

	return at_least_one_sid_change;
}


/**
 * @brief at least one RND flag changed now or in the last few packets?
 *
 * @param ctxt               The generic compression context
 * @param oa_repetitions_nr  The number of Optimistic Approach repetitions
 * @return                   true if at least one RND flag changed now or in
 *                           last few packets, false otherwise
 */
static inline bool does_at_least_one_rnd_change(const struct rohc_comp_rfc3095_ctxt *const ctxt,
                                                const uint8_t oa_repetitions_nr)
{
	bool at_least_one_rnd_change = false;
	size_t ip_hdr_pos;

	for(ip_hdr_pos = 0; ip_hdr_pos < ctxt->ip_hdr_nr; ip_hdr_pos++)
	{
		const struct ip_header_info *const ip_ctxt = &(ctxt->ip_ctxts[ip_hdr_pos]);

		if(ip_ctxt->version == IPV4 && ip_ctxt->info.v4.rnd_count < oa_repetitions_nr)
		{
			at_least_one_rnd_change = true;
		}
	}

	return at_least_one_rnd_change;
}

#endif

