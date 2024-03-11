// Generated from ifcc.g4 by ANTLR 4.7.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ifccLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, RETURN=9, 
		CONST=10, INT=11, VAR=12, ADD_SUB=13, MULT_DIV=14, COMMENT=15, DIRECTIVE=16, 
		WS=17;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "RETURN", 
			"CONST", "INT", "VAR", "ADD_SUB", "MULT_DIV", "COMMENT", "DIRECTIVE", 
			"WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'main'", "'('", "')'", "'{'", "'}'", "','", "';'", "'='", "'return'", 
			null, "'int'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, "RETURN", "CONST", 
			"INT", "VAR", "ADD_SUB", "MULT_DIV", "COMMENT", "DIRECTIVE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public ifccLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ifcc.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\23p\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3"+
		"\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\6\13A\n\13\r\13\16\13B\3\f\3\f"+
		"\3\f\3\f\3\r\3\r\7\rK\n\r\f\r\16\rN\13\r\3\16\3\16\3\17\3\17\3\20\3\20"+
		"\3\20\3\20\7\20X\n\20\f\20\16\20[\13\20\3\20\3\20\3\20\3\20\3\20\3\21"+
		"\3\21\7\21d\n\21\f\21\16\21g\13\21\3\21\3\21\3\21\3\21\3\22\3\22\3\22"+
		"\3\22\4Ye\2\23\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16"+
		"\33\17\35\20\37\21!\22#\23\3\2\b\3\2\62;\4\2C\\c|\5\2\62;C\\c|\4\2--/"+
		"/\4\2,,\61\61\5\2\13\f\17\17\"\"\2s\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2"+
		"\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23"+
		"\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2"+
		"\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\3%\3\2\2\2\5*\3\2\2\2\7,\3\2\2"+
		"\2\t.\3\2\2\2\13\60\3\2\2\2\r\62\3\2\2\2\17\64\3\2\2\2\21\66\3\2\2\2\23"+
		"8\3\2\2\2\25@\3\2\2\2\27D\3\2\2\2\31H\3\2\2\2\33O\3\2\2\2\35Q\3\2\2\2"+
		"\37S\3\2\2\2!a\3\2\2\2#l\3\2\2\2%&\7o\2\2&\'\7c\2\2\'(\7k\2\2()\7p\2\2"+
		")\4\3\2\2\2*+\7*\2\2+\6\3\2\2\2,-\7+\2\2-\b\3\2\2\2./\7}\2\2/\n\3\2\2"+
		"\2\60\61\7\177\2\2\61\f\3\2\2\2\62\63\7.\2\2\63\16\3\2\2\2\64\65\7=\2"+
		"\2\65\20\3\2\2\2\66\67\7?\2\2\67\22\3\2\2\289\7t\2\29:\7g\2\2:;\7v\2\2"+
		";<\7w\2\2<=\7t\2\2=>\7p\2\2>\24\3\2\2\2?A\t\2\2\2@?\3\2\2\2AB\3\2\2\2"+
		"B@\3\2\2\2BC\3\2\2\2C\26\3\2\2\2DE\7k\2\2EF\7p\2\2FG\7v\2\2G\30\3\2\2"+
		"\2HL\t\3\2\2IK\t\4\2\2JI\3\2\2\2KN\3\2\2\2LJ\3\2\2\2LM\3\2\2\2M\32\3\2"+
		"\2\2NL\3\2\2\2OP\t\5\2\2P\34\3\2\2\2QR\t\6\2\2R\36\3\2\2\2ST\7\61\2\2"+
		"TU\7,\2\2UY\3\2\2\2VX\13\2\2\2WV\3\2\2\2X[\3\2\2\2YZ\3\2\2\2YW\3\2\2\2"+
		"Z\\\3\2\2\2[Y\3\2\2\2\\]\7,\2\2]^\7\61\2\2^_\3\2\2\2_`\b\20\2\2` \3\2"+
		"\2\2ae\7%\2\2bd\13\2\2\2cb\3\2\2\2dg\3\2\2\2ef\3\2\2\2ec\3\2\2\2fh\3\2"+
		"\2\2ge\3\2\2\2hi\7\f\2\2ij\3\2\2\2jk\b\21\2\2k\"\3\2\2\2lm\t\7\2\2mn\3"+
		"\2\2\2no\b\22\3\2o$\3\2\2\2\7\2BLYe\4\b\2\2\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}