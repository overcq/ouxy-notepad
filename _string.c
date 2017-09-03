//=============================================================================
const char *E_string_Q_xml_S_from_entity_re = "&(?:#\\d{1,10}|#[xX][\\dA-Fa-f]{1,8}|quot|amp|apos|lt|gt|nbsp|iexcl|cent|pound|curren|yen|brvbar|sect|uml|copy|ordf|laquo|not|shy|reg|macr|deg|plusmn|sup2|sup3|acute|micro|para|middot|cedil|sup1|ordm|raquo|frac14|frac12|frac34|iquest|Agrave|Aacute|Acirc|Atilde|Auml|Aring|AElig|Ccedil|Egrave|Eacute|Ecirc|Euml|Igrave|Iacute|Icirc|Iuml|ETH|Ntilde|Ograve|Oacute|Ocirc|Otilde|Ouml|times|Oslash|Ugrave|Uacute|Ucirc|Uuml|Yacute|THORN|szlig|agrave|aacute|acirc|atilde|auml|aring|aelig|ccedil|egrave|eacute|ecirc|euml|igrave|iacute|icirc|iuml|eth|ntilde|ograve|oacute|ocirc|otilde|ouml|divide|oslash|ugrave|uacute|ucirc|uuml|yacute|thorn|yuml|OElig|oelig|Scaron|scaron|Yuml|fnof|circ|tilde|Alpha|Beta|Gamma|Delta|Epsilon|Zeta|Eta|Theta|Iota|Kappa|Lambda|Mu|Nu|Xi|Omicron|Pi|Rho|Sigma|Tau|Upsilon|Phi|Chi|Psi|Omega|alpha|beta|gamma|delta|epsilon|zeta|eta|theta|iota|kappa|lambda|mu|nu|xi|omicron|pi|rho|sigmaf|sigma|tau|upsilon|phi|chi|psi|omega|thetasym|upsih|piv|ensp|emsp|thinsp|zwnj|zwj|lrm|rlm|ndash|mdash|lsquo|rsquo|sbquo|ldquo|rdquo|bdquo|dagger|Dagger|bull|hellip|permil|prime|Prime|lsaquo|rsaquo|oline|frasl|euro|image|weierp|real|trade|alefsym|larr|uarr|rarr|darr|harr|crarr|lArr|uArr|rArr|dArr|hArr|forall|part|exist|empty|nabla|isin|notin|ni|prod|sum|minus|lowast|radic|prop|infin|ang|and|or|cap|cup|int|there4|sim|cong|asymp|ne|equiv|le|ge|sub|sup|nsub|sube|supe|oplus|otimes|perp|sdot|vellip|lceil|rceil|lfloor|rfloor|lang|rang|loz|spades|clubs|hearts|diams);";
const char *E_string_Q_xml_S_to_entity_re = "[&<>]";
const struct E_string_Q_xml_Z_entity_table
{ char *n;
  gunichar u;
} E_string_Q_xml_S_entity_table[] =
{ { "amp", 0x26 }
, { "lt", 0x3C }
, { "gt", 0x3E }
, { "quot", 0x22 }
, { "apos", 0x27 }
, { "nbsp", 0xA0 }
, { "iexcl", 0xA1 }
, { "cent", 0xA2 }
, { "pound", 0xA3 }
, { "curren", 0xA4 }
, { "yen", 0xA5 }
, { "brvbar", 0xA6 }
, { "sect", 0xA7 }
, { "uml", 0xA8 }
, { "copy", 0xA9 }
, { "ordf", 0xAA }
, { "laquo", 0xAB }
, { "not", 0xAC }
, { "shy", 0xAD }
, { "reg", 0xAE }
, { "macr", 0xAF }
, { "deg", 0xB0 }
, { "plusmn", 0xB1 }
, { "sup2", 0xB2 }
, { "sup3", 0xB3 }
, { "acute", 0xB4 }
, { "micro", 0xB5 }
, { "para", 0xB6 }
, { "middot", 0xB7 }
, { "cedil", 0xB8 }
, { "sup1", 0xB9 }
, { "ordm", 0xBA }
, { "raquo", 0xBB }
, { "frac14", 0xBC }
, { "frac12", 0xBD }
, { "frac34", 0xBE }
, { "iquest", 0xBF }
, { "Agrave", 0xC0 }
, { "Aacute", 0xC1 }
, { "Acirc", 0xC2 }
, { "Atilde", 0xC3 }
, { "Auml", 0xC4 }
, { "Aring", 0xC5 }
, { "AElig", 0xC6 }
, { "Ccedil", 0xC7 }
, { "Egrave", 0xC8 }
, { "Eacute", 0xC9 }
, { "Ecirc", 0xCA }
, { "Euml", 0xCB }
, { "Igrave", 0xCC }
, { "Iacute", 0xCD }
, { "Icirc", 0xCE }
, { "Iuml", 0xCF }
, { "ETH", 0xD0 }
, { "Ntilde", 0xD1 }
, { "Ograve", 0xD2 }
, { "Oacute", 0xD3 }
, { "Ocirc", 0xD4 }
, { "Otilde", 0xD5 }
, { "Ouml", 0xD6 }
, { "times", 0xD7 }
, { "Oslash", 0xD8 }
, { "Ugrave", 0xD9 }
, { "Uacute", 0xDA }
, { "Ucirc", 0xDB }
, { "Uuml", 0xDC }
, { "Yacute", 0xDD }
, { "THORN", 0xDE }
, { "szlig", 0xDF }
, { "agrave", 0xE0 }
, { "aacute", 0xE1 }
, { "acirc", 0xE2 }
, { "atilde", 0xE3 }
, { "auml", 0xE4 }
, { "aring", 0xE5 }
, { "aelig", 0xE6 }
, { "ccedil", 0xE7 }
, { "egrave", 0xE8 }
, { "eacute", 0xE9 }
, { "ecirc", 0xEA }
, { "euml", 0xEB }
, { "igrave", 0xEC }
, { "iacute", 0xED }
, { "icirc", 0xEE }
, { "iuml", 0xEF }
, { "eth", 0xF0 }
, { "ntilde", 0xF1 }
, { "ograve", 0xF2 }
, { "oacute", 0xF3 }
, { "ocirc", 0xF4 }
, { "otilde", 0xF5 }
, { "ouml", 0xF6 }
, { "divide", 0xF7 }
, { "oslash", 0xF8 }
, { "ugrave", 0xF9 }
, { "uacute", 0xFA }
, { "ucirc", 0xFB }
, { "uuml", 0xFC }
, { "yacute", 0xFD }
, { "thorn", 0xFE }
, { "yuml", 0xFF }
, { "OElig", 0x152 }
, { "oelig", 0x153 }
, { "Scaron", 0x160 }
, { "scaron", 0x161 }
, { "Yuml", 0x178 }
, { "fnof", 0x192 }
, { "circ", 0x2C6 }
, { "tilde", 0x2DC }
, { "Alpha", 0x391 }
, { "Beta", 0x392 }
, { "Gamma", 0x393 }
, { "Delta", 0x394 }
, { "Epsilon", 0x395 }
, { "Zeta", 0x396 }
, { "Eta", 0x397 }
, { "Theta", 0x398 }
, { "Iota", 0x399 }
, { "Kappa", 0x39A }
, { "Lambda", 0x39B }
, { "Mu", 0x39C }
, { "Nu", 0x39D }
, { "Xi", 0x39E }
, { "Omicron", 0x39F }
, { "Pi", 0x3A0 }
, { "Rho", 0x3A1 }
, { "Sigma", 0x3A3 }
, { "Tau", 0x3A4 }
, { "Upsilon", 0x3A5 }
, { "Phi", 0x3A6 }
, { "Chi", 0x3A7 }
, { "Psi", 0x3A8 }
, { "Omega", 0x3A9 }
, { "alpha", 0x3B1 }
, { "beta", 0x3B2 }
, { "gamma", 0x3B3 }
, { "delta", 0x3B4 }
, { "epsilon", 0x3B5 }
, { "zeta", 0x3B6 }
, { "eta", 0x3B7 }
, { "theta", 0x3B8 }
, { "iota", 0x3B9 }
, { "kappa", 0x3BA }
, { "lambda", 0x3BB }
, { "mu", 0x3BC }
, { "nu", 0x3BD }
, { "xi", 0x3BE }
, { "omicron", 0x3BF }
, { "pi", 0x3C0 }
, { "rho", 0x3C1 }
, { "sigmaf", 0x3C2 }
, { "sigma", 0x3C3 }
, { "tau", 0x3C4 }
, { "upsilon", 0x3C5 }
, { "phi", 0x3C6 }
, { "chi", 0x3C7 }
, { "psi", 0x3C8 }
, { "omega", 0x3C9 }
, { "thetasym", 0x3D1 }
, { "upsih", 0x3D2 }
, { "piv", 0x3D6 }
, { "ensp", 0x2002 }
, { "emsp", 0x2003 }
, { "thinsp", 0x2009 }
, { "zwnj", 0x200C }
, { "zwj", 0x200D }
, { "lrm", 0x200E }
, { "rlm", 0x200F }
, { "ndash", 0x2013 }
, { "mdash", 0x2014 }
, { "lsquo", 0x2018 }
, { "rsquo", 0x2019 }
, { "sbquo", 0x201A }
, { "ldquo", 0x201C }
, { "rdquo", 0x201D }
, { "bdquo", 0x201E }
, { "dagger", 0x2020 }
, { "Dagger", 0x2021 }
, { "bull", 0x2022 }
, { "hellip", 0x2026 }
, { "permil", 0x2030 }
, { "prime", 0x2032 }
, { "Prime", 0x2033 }
, { "lsaquo", 0x2039 }
, { "rsaquo", 0x203A }
, { "oline", 0x203E }
, { "frasl", 0x2044 }
, { "euro", 0x20AC }
, { "image", 0x2111 }
, { "weierp", 0x2118 }
, { "real", 0x211C }
, { "trade", 0x2122 }
, { "alefsym", 0x2135 }
, { "larr", 0x2190 }
, { "uarr", 0x2191 }
, { "rarr", 0x2192 }
, { "darr", 0x2193 }
, { "harr", 0x2194 }
, { "crarr", 0x21B5 }
, { "lArr", 0x21D0 }
, { "uArr", 0x21D1 }
, { "rArr", 0x21D2 }
, { "dArr", 0x21D3 }
, { "hArr", 0x21D4 }
, { "forall", 0x2200 }
, { "part", 0x2202 }
, { "exist", 0x2203 }
, { "empty", 0x2205 }
, { "nabla", 0x2207 }
, { "isin", 0x2208 }
, { "notin", 0x2209 }
, { "ni", 0x220B }
, { "prod", 0x220F }
, { "sum", 0x2211 }
, { "minus", 0x2212 }
, { "lowast", 0x2217 }
, { "radic", 0x221A }
, { "prop", 0x221D }
, { "infin", 0x221E }
, { "ang", 0x2220 }
, { "and", 0x2227 }
, { "or", 0x2228 }
, { "cap", 0x2229 }
, { "cup", 0x222A }
, { "int", 0x222B }
, { "there4", 0x2234 }
, { "sim", 0x223C }
, { "cong", 0x2245 }
, { "asymp", 0x2248 }
, { "ne", 0x2260 }
, { "equiv", 0x2261 }
, { "le", 0x2264 }
, { "ge", 0x2265 }
, { "sub", 0x2282 }
, { "sup", 0x2283 }
, { "nsub", 0x2284 }
, { "sube", 0x2286 }
, { "supe", 0x2287 }
, { "oplus", 0x2295 }
, { "otimes", 0x2297 }
, { "perp", 0x22A5 }
, { "sdot", 0x22C5 }
, { "vellip", 0x22EE }
, { "lceil", 0x2308 }
, { "rceil", 0x2309 }
, { "lfloor", 0x230A }
, { "rfloor", 0x230B }
, { "lang", 0x2329 }
, { "rang", 0x232A }
, { "loz", 0x25CA }
, { "spades", 0x2660 }
, { "clubs", 0x2663 }
, { "hearts", 0x2665 }
, { "diams", 0x2666 }
};
//=============================================================================
void *
E_string_Q_bit_array_M( unsigned count
){  char *p = g_malloc(( count + 7 ) / 8 );
    *( p + ( count - 1 ) / 8 ) = 0;
    return p;
}
int
E_string_Q_bit_array_R( void *p
, unsigned i
){  return *(( char * ) p + i / 8 ) & ( 1 << ( i % 8 ));
} //‘ndfn’: uzupełnić o alternatywę “bt”.
int
E_string_Q_bit_array_R_all_zero( void *p
, unsigned count
){  for( unsigned i = 0; i < ( count - 1 ) / 8; i++ )
        if( !*(( char * ) p + i ))
            return no;
    return !( *(( char * ) p + ( count - 1 ) / 8 ) & (( 1 << (( count - 1 ) % 8 + 1 )) - 1 ));
} //‘ndfn’: uzupełnić o alternatywę “btf”?
int
E_string_Q_bit_array_R_all_one( void *p
, unsigned count
){  for( unsigned i = 0; i < ( count - 1 ) / 8; i++ )
        if( ~*(( char * ) p + i ))
            return no;
    return !( *(( char * ) p + ( count - 1 ) / 8 ) ^ (( 1 << (( count - 1 ) % 8 + 1 )) - 1 ));
} //‘ndfn’: uzupełnić o alternatywę “btf”?
void
E_string_Q_bit_array_P_zero( void *p
, unsigned i
){  *(( char * ) p + i / 8 ) &= ~( 1 << ( i % 8 ));
} //‘ndfn’: uzupełnić o alternatywę “bts”.
void
E_string_Q_bit_array_P_one( void *p
, unsigned i
){  *(( char * ) p + i / 8 ) |= 1 << ( i % 8 );
} //‘ndfn’: uzupełnić o alternatywę “bts”.
void
E_string_Q_bit_array_P_all_zero( void *p
, unsigned count
){  memset( p, 0, ( count + 7 ) / 8 );
}
void
E_string_Q_bit_array_W( void *p
){  g_free(p);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned
E_string_Q_unistring_R_length( gunichar *s_
){  gunichar *s = s_;
    while( *s )
        s++;
    return s - s_;
}
void
E_string_Q_unistring_P_to_lower( gunichar *s
){  while( *s )
    {   *s = g_unichar_tolower( *s );
        s++;
    }
}
gunichar *
E_string_Q_unistring_R_substr_after( gunichar *s
, gunichar *f_
){  gunichar *f = f_;
    while( *s )
    {   if( !*f )
            return s;
        if( *s == *f )
            f++;
        else if( f != f_ )
        {   s -= f - f_;
            f = f_;
        }
        s++;
    }
    return *f ? null : s;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gboolean
E_string_Z_gtk_I_eval_I_replace_from_entities( const GMatchInfo *match_info
, GString *result
, void *data
){  char *s = g_match_info_fetch( match_info, 0 );
    s[ strlen(s) - 1 ] = '\0';
    if( s[1] == '#' )
        g_string_append_unichar( result, g_ascii_strtoull( s + ( s[2] == 'x' || s[2] == 'X' ? 3 : 2 ), null, s[2] == 'x' || s[2] == 'X' ? 16 : 10 ));
    else
    {   const struct E_string_Q_xml_Z_entity_table *p = &E_string_Q_xml_S_entity_table[0];
        while( strcmp( p->n, s + 1 ))
            p++;
        g_string_append_unichar( result, p->u );
    }
    g_free(s);
    return no;
}
gboolean
E_string_Q_xml_Z_gtk_I_eval_I_replace_to_entities( const GMatchInfo *match_info
, GString *result
, void *data
){  char *s = g_match_info_fetch( match_info, 0 );
    const struct E_string_Q_xml_Z_entity_table *p = &E_string_Q_xml_S_entity_table[0];
    while( p->u != *s )
        p++;
    g_string_append_c( result, '&' );
    g_string_append( result, p->n );
    g_string_append_c( result, ';' );
    g_free(s);
    return no;
}
//=============================================================================
