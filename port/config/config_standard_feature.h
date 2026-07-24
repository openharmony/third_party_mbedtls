/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * \file config_standard_feature.h
 *
 * \brief Small-system (LiteOS-A) / Standard-system MbedTLS configuration entry.
 *
 * Includes the shared non-module base configuration plus the two macros that
 * distinguish the legacy config_liteos_a.h from config_liteos_m.h:
 *   - MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
 *   - MBEDTLS_TIMING_C
 * Module macros are injected by GN via MBEDTLS_FEATURE_DEFINES.
 *
 * This file is referenced via MBEDTLS_CONFIG_FILE by BUILD.gn for liteos_a and
 * for the standard (non-lite) build.
 */

#ifndef MBEDTLS_CONFIG_STANDARD_FEATURE_H
#define MBEDTLS_CONFIG_STANDARD_FEATURE_H

#include "config_feature_base.h"

#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_TIMING_C

#endif /* MBEDTLS_CONFIG_STANDARD_FEATURE_H */
