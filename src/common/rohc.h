/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file rohc.h
 * @brief ROHC common definitions and routines 
 * @author Didier Barvaux <didier.barvaux@toulouse.viveris.com>
 * @author The hackers from ROHC for Linux
 */

#ifndef ROHC_H
#define ROHC_H

/**
 * \mainpage
 *
 * <h2>Introduction</h2>
 * 
 * <p>
 * This piece of software is an implementation of RObust Header Compression for
 * Linux (or other Unix-compatible OS). The library can be used to add ROHC
 * compression/decompression capabilities to an application.
 * </p>
 *
 * <p>Important links:
 *  <ul>
 *    <li>Official website: <a href="http://launchpad.net/rohc">
 *                           http://launchpad.net/rohc</a></li>
 *    <li>Mailing list: <a href="mailto:rohc@lists.launchpad.net">
 *                       rohc@lists.launchpad.net</a></li>
 *    <li>Mailing list archives: <a href="http://lists.launchpad.net/rohc/">
 *                                http://lists.launchpad.net/rohc/</a></li>
 *    <li>Bugtracker: <a href="http://bugs.launchpad.net/rohc">
 *                     http://bugs.launchpad.net/rohc</a></li>
 *  </ul>
 * </p>
 *
 * <p>The list of features implemented (or not yet implemented) in the ROHC
 * library is available on a separate page: \ref features</p>
 *
 * <p>The APIs for ROHC common, compression and decompression are also available on
 * separate pages:
 *  <ul>
 *    <li>\ref rohc_common</li>
 *    <li>\ref rohc_comp</li>
 *    <li>\ref rohc_decomp</li>
 *  </ul>
 * </p>
 * 
 * <h2>License</h2>
 * 
 * <p>
 * The project is licensed under GPL2+, see the <a
 * href="http://bazaar.launchpad.net/%7Edidier-barvaux/rohc/main/annotate/head%3A/COPYING">
 * COPYING</a> and <a
 * href="http://bazaar.launchpad.net/%7Edidier-barvaux/rohc/main/annotate/head%3A/AUTHORS">
 * AUTHORS</a> files for more details.
 * </p>
 * 
 * <h2>Libraries</h2>
 * 
 * <p>
 * The sources are in the src subdirectory. The sources are separated into
 * three libraries:
 *  <ul>
 *   <li>a library that contains the routines used for both the compression
 *       and the decompression processes</li>
 *   <li>a library that handles the compression process</li>
 *   <li>a library that handles the decompression process</li>
 *  </ul>
 * </p>
 * 
 * <p>See the <a href="http://bazaar.launchpad.net/%7Edidier-barvaux/rohc/main/annotate/head%3A/INSTALL">
 * INSTALL</a> file to learn to build the libraries.</p>
 * 
 * <h2>Non-regression tests</h2>
 * 
 * <p>
 * The test subdirectory contains a test application. See the header of the
 * test.c file for details. There is also a report tool that tests the ROHC
 * libraries with several IP flows and outputs an HTML page with the test
 * results.
 * </p>
 * 
 * <p>See the <a href="http://bazaar.launchpad.net/%7Edidier-barvaux/rohc/main/annotate/head%3A/INSTALL">
 * INSTALL</a> file to learn how to use the non-regression and report tools.</p>
 * 
 * <h2>References</h2>
 * 
 * <table style="border-collapse: collapse; border: solid thin black;">
 *  <tr>
 *   <td>RFC 3095</td>
 *   <td>
 *    <p>
 *     RObust Header Compression (ROHC): Framework and four profiles: RTP,
 *     UDP, ESP, and uncompressed.<br>
 *      <a href="http://www.ietf.org/rfc/rfc3095.txt">
 *       http://www.ietf.org/rfc/rfc3095.txt</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>RFC 3096</td>
 *   <td>
 *    <p>
 *     Requirements for robust IP/UDP/RTP header compression.<br>
 *      <a href="http://www.ietf.org/rfc/rfc3096.txt">
 *       http://www.ietf.org/rfc/rfc3096.txt</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>RFC 3828</td>
 *   <td>
 *    <p>
 *     The Lightweight User Datagram Protocol (UDP-Lite).<br>
 *     <a href="http://www.ietf.org/rfc/rfc3828.txt">
 *     http://www.ietf.org/rfc/rfc3828.txt</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>RFC 3843
 *   <td>
 *    <p>
 *     RObust Header Compression (ROHC): A Compression Profile for IP.<br>
 *     <a href="http://www.ietf.org/rfc/rfc3843.txt">
 *     http://www.ietf.org/rfc/rfc3843.txt</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>RFC 4019</td>
 *   <td>
 *    <p>
 *     RObust Header Compression (ROHC): Profiles for User Datagram Protocol
 *     (UDP) Lite.<br>
 *     <a href="http://www.ietf.org/rfc/rfc4019.txt">
 *     http://www.ietf.org/rfc/rfc4019.txt</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>ROHC library</td>
 *   <td>
 *    <p>
 *     The Open Source ROHC library described by the documentation you are
 *     currently reading.<br>
 *     <a href="http://launchpad.net/rohc">http://launchpad.net/rohc</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>ROHC Linux</td>
 *   <td>
 *    <p>
 *     A GPL-licensed implementation of ROHC over PPP for the 2.4 Linux
 *     kernel. The ROHC library is mainly based on this software.<br>
 *     <a href="http://rohc.sourceforge.net/">http://rohc.sourceforge.net/</a>
 *    </p>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>UDP-Lite</td>
 *   <td>
 *    <p>
 *     An UDP-Lite implementation for the Linux kernel.<br>
 *     <a href="http://www.erg.abdn.ac.uk/users/gerrit/udp-lite/">
 *     http://www.erg.abdn.ac.uk/users/gerrit/udp-lite/</a>
 *    </p>
 *   </td>
 *  </tr>
 * </table>
 */


/**
 * \page features Library features
 *
 * <p>Unsupported features are in <span style="color: red;">red</span>.</p>
 * <p>Limitations are in <span style="color: orange;">orange</span>.</p>
 *
 * <h2>Main features</h2>
 *
 * <ul>
 *  <li>ROHC compression</li>
 *  <li>ROHC decompression</li>
 *  <li>ROHC channels: small and large Channel IDs (CIDs)</li>
 *  <li>
 *    ROHC modes:
 *    <ul>
 *     <li>Unidirectional mode (U-mode)</li>
 *     <li>Bidirectional Optimistic mode (O-mode)</li>
 *     <li style="color: red;">Bidirectional Reliable mode (R-mode)</li>
 *    </ul>
 *  </li>
 *  <li>
 *   ROHC states:
 *   <ul>
 *    <li>Initialization & Refresh (IR)</li>
 *    <li>First Order (FO)</li>
 *    <li>Second Order (SO)</li>
 *   </ul>
 *  </li>
 *  <li>
 *   Feedback:
 *   <ul>
 *    <li>Feedback packets</li>
 *    <li>Piggy-backed feedbacks</li>
 *    <li>Negative ACKs</li>
 *   </ul>
 *  </li>
 *  <li>
 *   ROHC packets:
 *   <ul>
 *    <li>Feedback packets (RFC 3095, §5.2.1 and §5.2.2)</li>
 *    <li>
 *     IR packet (RFC 3095, §5.2.3)
 *     <ul>
 *      <li style="color: orange;">Optional dynamic part is always sent</li>
 *     </ul>
 *    </li>
 *    <li>IR-DYN packet (RFC 3095, §5.2.3)</li>
 *    <li>
 *     Packet type 0 (RFC 3095, §5.7.1)
 *     <ul>
 *      <li>UO-0</li>
 *      <li style="color: red;">R-0</li>
 *      <li style="color: red;">R-0-CRC</li>
 *     </ul>
 *    </li>
 *    <li style="color: red;">
 *     Packet type 1 for R-mode (RFC 3095, §5.7.2)
 *     <ul>
 *      <li style="color: red;">R-1</li>
 *      <li style="color: red;">R-1-TS</li>
 *      <li style="color: red;">R-1-ID</li>
 *     </ul>
 *    </li>
 *    <li>
 *     Packet type 1 for U/O-mode (RFC 3095, §5.7.3)
 *     <ul>
 *      <li>UO-1</li>
 *      <li>UO-1-ID</li>
 *      <li>UO-1-TS</li>
 *     </ul>
 *    </li>
 *    <li>
 *     Packet type 2 (RFC 3095, §5.7.4)
 *     <ul>
 *      <li>UOR-2</li>
 *     </ul>
 *    </li>
 *   </ul>
 *  </li>
 *  <li>Actions upon CRC failure (RFC 3095, §5.3.2.2.3, §5.3.2.2.4 and §5.3.2.2.5)</li>
 * </ul>
 *
 * <h2>ROHC profiles</h2>
 *
 * <ul>
 *  <li>Uncompressed (0x0000)</li>
 *  <li>RTP (0x0001)</li>
 *  <li>UDP (0x0002)</li>
 *  <li style="color: red;">ESP (0x0003)</li>
 *  <li>IP-only (0x0004)</li>
 *  <li style="color: red;">TCP (0x0006)</li>
 *  <li>UDP-Light (0x0008)</li>
 * </ul>
 *
 * <h2>Features shared by all supported profiles</h2>
 *
 * <ul>
 *  <li>Compression of up to two IPv4/IPv6 headers</li>
 *  <li style="color: red;">Compressed IPv4 Header Extension List (RFC 3095, §5.8.4.1 & §5.8.5.1)</li>
 *  <li>Compressed IPv6 Header Extension List (RFC 3095, §5.8.4.1 & §5.8.5.1)</li>
 *  <li>Authentication Header (AH) Compression (RFC 3095, §5.8.4.2)</li>
 *  <li style="color: red;">Encapsulating Security Payload Header (ESP) Compression (RFC 3095, §5.8.4.3)</li>
 *  <li style="color: red;">GRE Header Compression (RFC 3095, §5.8.4.4)</li>
 *  <li>Forced context reinitialization controled by the user</li>
 *  <li>Fixed sizes parameters in order to specify the size of ROHC packets</li>
 *  <li style="color: red;">Optional Reverse decompression (RFC 3095, §6.1)</li>
 *  <li style="color: red;">ROHC segmentation (RFC 3095, §5.2.5)</li>
 * </ul>
 *
 * <h2>Profile-specific features</h2>
 *
 * <table style="border-collapse: collapse; border: solid thin black;">
 *  <tr>
 *   <td>Uncompressed</td>
 *   <td>
 *    &nbsp;
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>RTP</td>
 *   <td>
 *    <ul>
 *     <li style="color: red;">Compressed CSRC List (RFC 3095, §5.8.5.2)</li>
 *     <li style="color: red;">Timer-based compression of RTP Timestamp (RFC 3095, §4.5.4)</li>
 *    </ul>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>UDP</td>
 *   <td>
 *    &nbsp;
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>IP-only</td>
 *   <td>
 *    <ul>
 *     <li style="color: red;">more than 2 IPv4/IPv6 headers</li>
 *    </ul>
 *   </td>
 *  </tr>
 *  <tr>
 *   <td>UDP-Lite</td>
 *   <td>
 *    <ul>
 *     <li>Checksum Coverage (CC) compression</li>
 *    </ul>
 *   </td>
 *  </tr>
 * </table>
 *
 * <h2>Encoding methods</h2>
 *
 * <ul>
 *  <li>Least Significant Bits (LSB) encoding (RFC 3095, §4.5.1)</li>
 *  <li>Window-based LSB (W-LSB) encoding (RFC 3095, §4.5.2)</li>
 *  <li>Scaled RTP Timestamp encoding (RFC 3095, §4.5.3)</li>
 *  <li style="color: red;">Timer-based compression of RTP Timestamp (RFC 3095, §4.5.4)</li>
 *  <li>Offset IP-ID encoding (RFC 3095, §4.5.5)</li>
 *  <li>Self-describing variable-length (SDVL) values (RFC 3095, §4.5.6)</li>
 *  <li>
 *   Encoded values across several fields in compressed headers (RFC 3095, §4.5.7)
 *   <ul>
 *    <li style="color: orange;">Not fully respected: if more bits than stricly necessary are available, more bits are sent</li>
 *   </ul>
 *  </li>
 * </ul>
 *
 * <h2>Non-standard ROHC enhancements</h2>
 *
 * <ul>
 *  <li>
 *   Use of encapsulation padding for sending larger packets</li>
 *   <ul>
 *    <li style="color: orange;">Padding not used with Compressed IPv6 Header Extension List</li>
 *   </ul>
 *  </li>
 *  <li>Optional simplification of UOR-2-TS / UOR-2-ID packets to help distinguish them at decompressor</li>
 * </ul>
 */


#include <endian.h>


/*
 * Below are some return codes:
 */

/// Return code: the action done without problem
#define ROHC_OK                     1
/// Return code: the action done whithout problem and no data is returned
#define ROHC_OK_NO_DATA             0
/// Return code: the action can not proceed because no context is defined
#define ROHC_ERROR_NO_CONTEXT      -1
/// Return code: the action failed due to an unattended or malformed packet
#define ROHC_ERROR_PACKET_FAILED   -2
/// Return code: the action failed because the packet only contains feedback info
#define ROHC_FEEDBACK_ONLY         -3
/// Return code: the action failed due to a CRC failure
#define ROHC_ERROR_CRC             -4
/// Return code: the action encountered a problem
#define ROHC_ERROR                 -5
/// Return code: the packet needs to be parsed again
#define ROHC_NEED_REPARSE          -6

/// True value for the boolean type
#define ROHC_TRUE   1
/// False value for the boolean type
#define ROHC_FALSE  0
/// Boolean type that can only take two values: ROHC_TRUE or ROHC_FALSE
typedef unsigned char boolean;


/// @brief List of UDP ports associated with RTP streams
/// The port numbers must be separated by a comma
#define RTP_PORTS  1234, 36780, 33238, 5020, 5002



/**
 * ROHC operation modes (see 4.4 in the RFC 3095)
 */
typedef enum
{
	/// The Unidirectional mode (U-mode)
	U_MODE = 1,
	/// The Bidirectional Optimistic mode (O-mode)
	O_MODE = 2,
	/// The Bidirectional Reliable mode (R-mode)
	R_MODE = 3,
} rohc_mode;


/**
 * @brief ROHC medium (CID characteristics).
 */
struct medium
{
	/**
	 * @brief Large or small CID
	 *
	 * Possible values are: LARGE_CID, SMALL_CID. Small CID means CID in
	 * the \f$[0-15]\f$ interval and large CID means CID in the \f$[0-65535]\f$
	 * interval.
	 */
	enum {
		/// The context uses large CID (value in the \f$[0-65535]\f$ interval)
		LARGE_CID,
		/// The context uses small  CID (value in the \f$[0-15]\f$ interval)
		SMALL_CID,
	} cid_type;

	/// The maximum CID value
	int max_cid;
};


/*
 * ROHC profiles numbers allocated by the IANA (see 8 in the RFC 3095):
 */

/// The number allocated for the ROHC Uncompressed profile
#define ROHC_PROFILE_UNCOMPRESSED  0x0000
/// The number allocated for the ROHC RTP profile
#define ROHC_PROFILE_RTP           0x0001
/// The number allocated for the ROHC UDP profile
#define ROHC_PROFILE_UDP           0x0002
/// The number allocated for the ROHC IP-only profile (see 5 in the RFC 3843)
#define ROHC_PROFILE_IP            0x0004
/// The number allocated for the ROHC UDP-Lite profile (see 7 in the RFC 4019)
#define ROHC_PROFILE_UDPLITE       0x0008


/*
 * The limits for the compressor states changes:
 */

/// @brief The maximal number of packets sent in > IR states (= FO and SO
///        states) before changing back the state to IR (periodic refreshes)
#define CHANGE_TO_IR_COUNT  1700

/// @brief The maximal number of packets sent in > FO states (= SO state)
///        before changing back the state to FO (periodic refreshes)
#define CHANGE_TO_FO_COUNT  700

/// @brief Defines the minimal number of packets that must be sent while
///        in IR state before being able to switch the the FO state
#define MAX_IR_COUNT  3

/// @brief Defines the minimal number of packets that must be sent while
///        in FO state before being able to switch the the SO state
#define MAX_FO_COUNT  3


/*
 * The types of ROHC packets and their extensions:
 */

/// Defines an UO-0 packet
#define PACKET_UO_0      0
/// Defines an UO-1 packet
#define PACKET_UO_1      1
/// Defines an UOR-2 packet
#define PACKET_UOR_2     2
/// Defines an IR-DYN packet
#define PACKET_IR_DYN    3
/// Defines an IR packet
#define PACKET_IR        4
/// If packet type is not defined yet
#define PACKET_UNKNOWN   5
/// Defines an CCE packet (UDP-Lite profile only)
#define PACKET_CCE       6
/// Defines an CCE(OFF) packet (UDP-Lite profile only)
#define PACKET_CCE_OFF   7
/// Defines an UO-1-RTP packet
#define PACKET_UO_1_RTP  8
/// Defines an UO-1-ID packet
#define PACKET_UO_1_ID   9
/// Defines an UO-1-TS packet
#define PACKET_UO_1_TS  10
/// Defines an UO-2-RTP packet
#define PACKET_UOR_2_RTP 11
/// Defines an UO-2-ID packet
#define PACKET_UOR_2_ID  12
/// Defines an UO-2-TS packet
#define PACKET_UOR_2_TS  13

/// No extension for the UOR-2 packet
#define PACKET_NOEXT    (-1)
/// Defines the EXT-0 extension for the UOR-2 packet
#define PACKET_EXT_0     0
/// Defines the EXT-1 extension for the UOR-2 packet
#define PACKET_EXT_1     1
/// Defines the EXT-2 extension for the UOR-2 packet
#define PACKET_EXT_2     2
/// Defines the EXT-3 extension for the UOR-2 packet
#define PACKET_EXT_3     3


/*
 * Constants related to packet recovery after CRC failure:
 */

/// Whether to attempt packet recovery after CRC failure or not
#define CRC_ACTION  1


/*
 * Bitwised operations:
 */

#define GET_BIT_0_2(x)  ((*(x)) & 0x07)
#define GET_BIT_0_4(x)  ((*(x)) & 0x1f)
#define GET_BIT_0_3(x)  ((*(x)) & 0x0f)
#define GET_BIT_0_5(x)  ((*(x)) & 0x3f)
#define GET_BIT_0_6(x)  ((*(x)) & 0x7f)
#define GET_BIT_0_7(x)  ((*(x)) & 0xff)

#define GET_BIT_1_7(x)  ( ((*(x)) & 0xfe) >> 1 )
#define GET_BIT_3_4(x)  ( ((*(x)) & 0x18) >> 3 )
#define GET_BIT_3_5(x)  ( ((*(x)) & 0x38) >> 3 )
#define GET_BIT_3_6(x)  ( ((*(x)) & 0x78) >> 3 )
#define GET_BIT_3_7(x)  ( ((*(x)) & 0xf8) >> 3 )
#define GET_BIT_4_7(x)  ( ((*(x)) & 0xf0) >> 4 )
#define GET_BIT_5_7(x)  ( ((*(x)) & 0xe0) >> 5 )
#define GET_BIT_6_7(x)  ( ((*(x)) & 0xc0) >> 6 )
#define GET_BIT_4_6(x)  ( ((*(x)) & 0x70) >> 4 )

#define GET_BIT_0(x)  ((*(x)) & 0x01)
#define GET_BIT_1(x)  ((*(x)) & 0x02)
#define GET_BIT_2(x)  ((*(x)) & 0x04)
#define GET_BIT_3(x)  ((*(x)) & 0x08)
#define GET_BIT_4(x)  ((*(x)) & 0x10)
#define GET_BIT_5(x)  ((*(x)) & 0x20)
#define GET_BIT_6(x)  ((*(x)) & 0x40)
#define GET_BIT_7(x)  ((*(x)) & 0x80)

/// Convert GET_BIT_x values to 0 or 1, ex: GET_REAL(GET_BIT_5(data_ptr));
#define GET_REAL(x)	( (x) ? 1 : 0 )

/** Get the next 16 bits at the given memory location in Network Byte Order */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#	define GET_NEXT_16_BITS(x) \
		((((*((x) + 1)) << 8) & 0xff00) | ((*(x)) & 0x00ff))
#elif __BYTE_ORDER == __BIG_ENDIAN
#	define GET_NEXT_16_BITS(x) \
		((((*(x)) << 8) & 0xff00) | ((*((x) + 1)) & 0x00ff))
#else
#	error "Adjust your <bits/endian.h> defines"
#endif


/*
 * The flags for the IP changed fields:
 */

/// Indicates that the IPv4 Type Of Service field changed
#define MOD_TOS       0x0001
/// Indicates that the IPv4 Total Length field changed
#define MOD_TOT_LEN   0x0002
/// Indicates that the IPv4 Identification field changed
#define MOD_ID        0x0004
/// Indicates that the IPv4 Fragment Offset field changed
#define MOD_FRAG_OFF  0x0008
/// Indicates that the IPv4 Time To Live field changed
#define MOD_TTL       0x0010
/// Indicates that the IPv4 Protocol field changed
#define MOD_PROTOCOL  0x0020
/// Indicates that the IPv4 Checksum field changed
#define MOD_CHECK     0x0040
/// Indicates that the IPv4 Source Address field changed
#define MOD_SADDR     0x0080
/// Indicates that the IPv4 Destination Address field changed
#define MOD_DADDR     0x0100


/*
 *  The flags for the RTP changed fields:
 */

/// Indicates that the RTP Padding field changed
#define MOD_RTP_PADDING  0x0200
/// Indicates that the RTP Extension field changed
#define MOD_RTP_EXT      0x0400
/// Indicates that the RTP Marker field changed
#define MOD_RTP_M        0x0800
/// Indicates that the Payload Type field changed
#define MOD_RTP_PT       0x1000
/// Indicates that the Sequence Number field changed
#define MOD_RTP_SN       0x2000
/// Indicates that the Timestamp field changed
#define MOD_RTP_TS       0x4000
/// Indicates that the SSRC field changed
#define MOD_RTP_SSRC     0x8000


/*
 * Time-related constants:
 */

#define WEIGHT_OLD  1
#define WEIGHT_NEW  1


/*
 * System includes:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/in.h>

/*
 * Debug macros:
 */

/// Free a pointer plus set it to NULL to avoid hidden bugs
#define zfree(pointer) \
	do { \
		free(pointer); \
		pointer = NULL; \
	} while(0)


/**
 * @brief Get the current time in microseconds
 *
 * @return The current time in microseconds
 */
static inline unsigned int get_microseconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}


/**
 * @brief Get the current time in milliseconds
 *
 * @return The current time in milliseconds
 */
static inline unsigned int get_milliseconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

char *rohc_version(void);


/*
 * ROHC library includes:
 */

#include "crc.h"
#include "decode.h"
#include "ip_id.h"
#include "lsb.h"
#include "sdvl.h"
#include "wlsb.h"
#include "rtp.h"
#include "ip.h"


#endif

