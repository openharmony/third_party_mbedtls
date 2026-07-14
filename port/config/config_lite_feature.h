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
 * \file config_lite_feature.h
 *
 * \brief Mini-system (LiteOS-M) MbedTLS configuration entry.
 *
 * Includes only the shared non-module base configuration. Module macros are
 * injected by GN via MBEDTLS_FEATURE_DEFINES. Mini systems do not enable
 * MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED nor MBEDTLS_TIMING_C (the only
 * differences vs the small/standard entry, config_standard_feature.h).
 *
 * This file is referenced via MBEDTLS_CONFIG_FILE by BUILD.gn for liteos_m.
 */

#ifndef MBEDTLS_CONFIG_LITE_FEATURE_H
#define MBEDTLS_CONFIG_LITE_FEATURE_H

#include "config_feature_base.h"

#endif /* MBEDTLS_CONFIG_LITE_FEATURE_H */
