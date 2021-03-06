/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "prtypes.h"

namespace mozilla {
namespace unicode {

// Multi-character mappings (from SpecialCasing.txt) map a single Unicode
// value to a sequence of 2 or 3 Unicode characters. There are currently none
// defined outside the BMP, so we can use PRUnichar here. Unused trailing
// positions in mMappedChars are set to 0.
struct MultiCharMapping {
  PRUnichar mOriginalChar;
  PRUnichar mMappedChars[3];
};

// Return a pointer to the special case mapping for the given character;
// returns NULL if no such mapping is defined.
const MultiCharMapping* SpecialUpper(PRUint32 aCh);
const MultiCharMapping* SpecialLower(PRUint32 aCh);
const MultiCharMapping* SpecialTitle(PRUint32 aCh);

} // namespace unicode
} // namespace mozilla
