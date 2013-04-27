#ifndef LIGHT_ENGINE_FIND_HPP
#define LIGHT_ENGINE_FIND_HPP

/**
 * Find the DAC by listening for UDP packets.
 * This is a blocking call. 
 *
 * Returns string ip_address.
 */
std::string find_dac();

#endif
