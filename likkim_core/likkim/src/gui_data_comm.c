/*********************
 *      INCLUDES
 *********************/

#include "gui_comm.h"
#include "gui_data_comm.h"
#include "lib.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

static const char* const wordlist[] = {
    "abandon",  "ability",  "able",     "about",    "above",    "absent",
    "absorb",   "abstract", "absurd",   "abuse",    "access",   "accident",
    "account",  "accuse",   "achieve",  "acid",     "acoustic", "acquire",
    "across",   "act",      "action",   "actor",    "actress",  "actual",
    "adapt",    "add",      "addict",   "address",  "adjust",   "admit",
    "adult",    "advance",  "advice",   "aerobic",  "affair",   "afford",
    "afraid",   "again",    "age",      "agent",    "agree",    "ahead",
    "aim",      "air",      "airport",  "aisle",    "alarm",    "album",
    "alcohol",  "alert",    "alien",    "all",      "alley",    "allow",
    "almost",   "alone",    "alpha",    "already",  "also",     "alter",
    "always",   "amateur",  "amazing",  "among",    "amount",   "amused",
    "analyst",  "anchor",   "ancient",  "anger",    "angle",    "angry",
    "animal",   "ankle",    "announce", "annual",   "another",  "answer",
    "antenna",  "antique",  "anxiety",  "any",      "apart",    "apology",
    "appear",   "apple",    "approve",  "april",    "arch",     "arctic",
    "area",     "arena",    "argue",    "arm",      "armed",    "armor",
    "army",     "around",   "arrange",  "arrest",   "arrive",   "arrow",
    "art",      "artefact", "artist",   "artwork",  "ask",      "aspect",
    "assault",  "asset",    "assist",   "assume",   "asthma",   "athlete",
    "atom",     "attack",   "attend",   "attitude", "attract",  "auction",
    "audit",    "august",   "aunt",     "author",   "auto",     "autumn",
    "average",  "avocado",  "avoid",    "awake",    "aware",    "away",
    "awesome",  "awful",    "awkward",  "axis",     "baby",     "bachelor",
    "bacon",    "badge",    "bag",      "balance",  "balcony",  "ball",
    "bamboo",   "banana",   "banner",   "bar",      "barely",   "bargain",
    "barrel",   "base",     "basic",    "basket",   "battle",   "beach",
    "bean",     "beauty",   "because",  "become",   "beef",     "before",
    "begin",    "behave",   "behind",   "believe",  "below",    "belt",
    "bench",    "benefit",  "best",     "betray",   "better",   "between",
    "beyond",   "bicycle",  "bid",      "bike",     "bind",     "biology",
    "bird",     "birth",    "bitter",   "black",    "blade",    "blame",
    "blanket",  "blast",    "bleak",    "bless",    "blind",    "blood",
    "blossom",  "blouse",   "blue",     "blur",     "blush",    "board",
    "boat",     "body",     "boil",     "bomb",     "bone",     "bonus",
    "book",     "boost",    "border",   "boring",   "borrow",   "boss",
    "bottom",   "bounce",   "box",      "boy",      "bracket",  "brain",
    "brand",    "brass",    "brave",    "bread",    "breeze",   "brick",
    "bridge",   "brief",    "bright",   "bring",    "brisk",    "broccoli",
    "broken",   "bronze",   "broom",    "brother",  "brown",    "brush",
    "bubble",   "buddy",    "budget",   "buffalo",  "build",    "bulb",
    "bulk",     "bullet",   "bundle",   "bunker",   "burden",   "burger",
    "burst",    "bus",      "business", "busy",     "butter",   "buyer",
    "buzz",     "cabbage",  "cabin",    "cable",    "cactus",   "cage",
    "cake",     "call",     "calm",     "camera",   "camp",     "can",
    "canal",    "cancel",   "candy",    "cannon",   "canoe",    "canvas",
    "canyon",   "capable",  "capital",  "captain",  "car",      "carbon",
    "card",     "cargo",    "carpet",   "carry",    "cart",     "case",
    "cash",     "casino",   "castle",   "casual",   "cat",      "catalog",
    "catch",    "category", "cattle",   "caught",   "cause",    "caution",
    "cave",     "ceiling",  "celery",   "cement",   "census",   "century",
    "cereal",   "certain",  "chair",    "chalk",    "champion", "change",
    "chaos",    "chapter",  "charge",   "chase",    "chat",     "cheap",
    "check",    "cheese",   "chef",     "cherry",   "chest",    "chicken",
    "chief",    "child",    "chimney",  "choice",   "choose",   "chronic",
    "chuckle",  "chunk",    "churn",    "cigar",    "cinnamon", "circle",
    "citizen",  "city",     "civil",    "claim",    "clap",     "clarify",
    "claw",     "clay",     "clean",    "clerk",    "clever",   "click",
    "client",   "cliff",    "climb",    "clinic",   "clip",     "clock",
    "clog",     "close",    "cloth",    "cloud",    "clown",    "club",
    "clump",    "cluster",  "clutch",   "coach",    "coast",    "coconut",
    "code",     "coffee",   "coil",     "coin",     "collect",  "color",
    "column",   "combine",  "come",     "comfort",  "comic",    "common",
    "company",  "concert",  "conduct",  "confirm",  "congress", "connect",
    "consider", "control",  "convince", "cook",     "cool",     "copper",
    "copy",     "coral",    "core",     "corn",     "correct",  "cost",
    "cotton",   "couch",    "country",  "couple",   "course",   "cousin",
    "cover",    "coyote",   "crack",    "cradle",   "craft",    "cram",
    "crane",    "crash",    "crater",   "crawl",    "crazy",    "cream",
    "credit",   "creek",    "crew",     "cricket",  "crime",    "crisp",
    "critic",   "crop",     "cross",    "crouch",   "crowd",    "crucial",
    "cruel",    "cruise",   "crumble",  "crunch",   "crush",    "cry",
    "crystal",  "cube",     "culture",  "cup",      "cupboard", "curious",
    "current",  "curtain",  "curve",    "cushion",  "custom",   "cute",
    "cycle",    "dad",      "damage",   "damp",     "dance",    "danger",
    "daring",   "dash",     "daughter", "dawn",     "day",      "deal",
    "debate",   "debris",   "decade",   "december", "decide",   "decline",
    "decorate", "decrease", "deer",     "defense",  "define",   "defy",
    "degree",   "delay",    "deliver",  "demand",   "demise",   "denial",
    "dentist",  "deny",     "depart",   "depend",   "deposit",  "depth",
    "deputy",   "derive",   "describe", "desert",   "design",   "desk",
    "despair",  "destroy",  "detail",   "detect",   "develop",  "device",
    "devote",   "diagram",  "dial",     "diamond",  "diary",    "dice",
    "diesel",   "diet",     "differ",   "digital",  "dignity",  "dilemma",
    "dinner",   "dinosaur", "direct",   "dirt",     "disagree", "discover",
    "disease",  "dish",     "dismiss",  "disorder", "display",  "distance",
    "divert",   "divide",   "divorce",  "dizzy",    "doctor",   "document",
    "dog",      "doll",     "dolphin",  "domain",   "donate",   "donkey",
    "donor",    "door",     "dose",     "double",   "dove",     "draft",
    "dragon",   "drama",    "drastic",  "draw",     "dream",    "dress",
    "drift",    "drill",    "drink",    "drip",     "drive",    "drop",
    "drum",     "dry",      "duck",     "dumb",     "dune",     "during",
    "dust",     "dutch",    "duty",     "dwarf",    "dynamic",  "eager",
    "eagle",    "early",    "earn",     "earth",    "easily",   "east",
    "easy",     "echo",     "ecology",  "economy",  "edge",     "edit",
    "educate",  "effort",   "egg",      "eight",    "either",   "elbow",
    "elder",    "electric", "elegant",  "element",  "elephant", "elevator",
    "elite",    "else",     "embark",   "embody",   "embrace",  "emerge",
    "emotion",  "employ",   "empower",  "empty",    "enable",   "enact",
    "end",      "endless",  "endorse",  "enemy",    "energy",   "enforce",
    "engage",   "engine",   "enhance",  "enjoy",    "enlist",   "enough",
    "enrich",   "enroll",   "ensure",   "enter",    "entire",   "entry",
    "envelope", "episode",  "equal",    "equip",    "era",      "erase",
    "erode",    "erosion",  "error",    "erupt",    "escape",   "essay",
    "essence",  "estate",   "eternal",  "ethics",   "evidence", "evil",
    "evoke",    "evolve",   "exact",    "example",  "excess",   "exchange",
    "excite",   "exclude",  "excuse",   "execute",  "exercise", "exhaust",
    "exhibit",  "exile",    "exist",    "exit",     "exotic",   "expand",
    "expect",   "expire",   "explain",  "expose",   "express",  "extend",
    "extra",    "eye",      "eyebrow",  "fabric",   "face",     "faculty",
    "fade",     "faint",    "faith",    "fall",     "false",    "fame",
    "family",   "famous",   "fan",      "fancy",    "fantasy",  "farm",
    "fashion",  "fat",      "fatal",    "father",   "fatigue",  "fault",
    "favorite", "feature",  "february", "federal",  "fee",      "feed",
    "feel",     "female",   "fence",    "festival", "fetch",    "fever",
    "few",      "fiber",    "fiction",  "field",    "figure",   "file",
    "film",     "filter",   "final",    "find",     "fine",     "finger",
    "finish",   "fire",     "firm",     "first",    "fiscal",   "fish",
    "fit",      "fitness",  "fix",      "flag",     "flame",    "flash",
    "flat",     "flavor",   "flee",     "flight",   "flip",     "float",
    "flock",    "floor",    "flower",   "fluid",    "flush",    "fly",
    "foam",     "focus",    "fog",      "foil",     "fold",     "follow",
    "food",     "foot",     "force",    "forest",   "forget",   "fork",
    "fortune",  "forum",    "forward",  "fossil",   "foster",   "found",
    "fox",      "fragile",  "frame",    "frequent", "fresh",    "friend",
    "fringe",   "frog",     "front",    "frost",    "frown",    "frozen",
    "fruit",    "fuel",     "fun",      "funny",    "furnace",  "fury",
    "future",   "gadget",   "gain",     "galaxy",   "gallery",  "game",
    "gap",      "garage",   "garbage",  "garden",   "garlic",   "garment",
    "gas",      "gasp",     "gate",     "gather",   "gauge",    "gaze",
    "general",  "genius",   "genre",    "gentle",   "genuine",  "gesture",
    "ghost",    "giant",    "gift",     "giggle",   "ginger",   "giraffe",
    "girl",     "give",     "glad",     "glance",   "glare",    "glass",
    "glide",    "glimpse",  "globe",    "gloom",    "glory",    "glove",
    "glow",     "glue",     "goat",     "goddess",  "gold",     "good",
    "goose",    "gorilla",  "gospel",   "gossip",   "govern",   "gown",
    "grab",     "grace",    "grain",    "grant",    "grape",    "grass",
    "gravity",  "great",    "green",    "grid",     "grief",    "grit",
    "grocery",  "group",    "grow",     "grunt",    "guard",    "guess",
    "guide",    "guilt",    "guitar",   "gun",      "gym",      "habit",
    "hair",     "half",     "hammer",   "hamster",  "hand",     "happy",
    "harbor",   "hard",     "harsh",    "harvest",  "hat",      "have",
    "hawk",     "hazard",   "head",     "health",   "heart",    "heavy",
    "hedgehog", "height",   "hello",    "helmet",   "help",     "hen",
    "hero",     "hidden",   "high",     "hill",     "hint",     "hip",
    "hire",     "history",  "hobby",    "hockey",   "hold",     "hole",
    "holiday",  "hollow",   "home",     "honey",    "hood",     "hope",
    "horn",     "horror",   "horse",    "hospital", "host",     "hotel",
    "hour",     "hover",    "hub",      "huge",     "human",    "humble",
    "humor",    "hundred",  "hungry",   "hunt",     "hurdle",   "hurry",
    "hurt",     "husband",  "hybrid",   "ice",      "icon",     "idea",
    "identify", "idle",     "ignore",   "ill",      "illegal",  "illness",
    "image",    "imitate",  "immense",  "immune",   "impact",   "impose",
    "improve",  "impulse",  "inch",     "include",  "income",   "increase",
    "index",    "indicate", "indoor",   "industry", "infant",   "inflict",
    "inform",   "inhale",   "inherit",  "initial",  "inject",   "injury",
    "inmate",   "inner",    "innocent", "input",    "inquiry",  "insane",
    "insect",   "inside",   "inspire",  "install",  "intact",   "interest",
    "into",     "invest",   "invite",   "involve",  "iron",     "island",
    "isolate",  "issue",    "item",     "ivory",    "jacket",   "jaguar",
    "jar",      "jazz",     "jealous",  "jeans",    "jelly",    "jewel",
    "job",      "join",     "joke",     "journey",  "joy",      "judge",
    "juice",    "jump",     "jungle",   "junior",   "junk",     "just",
    "kangaroo", "keen",     "keep",     "ketchup",  "key",      "kick",
    "kid",      "kidney",   "kind",     "kingdom",  "kiss",     "kit",
    "kitchen",  "kite",     "kitten",   "kiwi",     "knee",     "knife",
    "knock",    "know",     "lab",      "label",    "labor",    "ladder",
    "lady",     "lake",     "lamp",     "language", "laptop",   "large",
    "later",    "latin",    "laugh",    "laundry",  "lava",     "law",
    "lawn",     "lawsuit",  "layer",    "lazy",     "leader",   "leaf",
    "learn",    "leave",    "lecture",  "left",     "leg",      "legal",
    "legend",   "leisure",  "lemon",    "lend",     "length",   "lens",
    "leopard",  "lesson",   "letter",   "level",    "liar",     "liberty",
    "library",  "license",  "life",     "lift",     "light",    "like",
    "limb",     "limit",    "link",     "lion",     "liquid",   "list",
    "little",   "live",     "lizard",   "load",     "loan",     "lobster",
    "local",    "lock",     "logic",    "lonely",   "long",     "loop",
    "lottery",  "loud",     "lounge",   "love",     "loyal",    "lucky",
    "luggage",  "lumber",   "lunar",    "lunch",    "luxury",   "lyrics",
    "machine",  "mad",      "magic",    "magnet",   "maid",     "mail",
    "main",     "major",    "make",     "mammal",   "man",      "manage",
    "mandate",  "mango",    "mansion",  "manual",   "maple",    "marble",
    "march",    "margin",   "marine",   "market",   "marriage", "mask",
    "mass",     "master",   "match",    "material", "math",     "matrix",
    "matter",   "maximum",  "maze",     "meadow",   "mean",     "measure",
    "meat",     "mechanic", "medal",    "media",    "melody",   "melt",
    "member",   "memory",   "mention",  "menu",     "mercy",    "merge",
    "merit",    "merry",    "mesh",     "message",  "metal",    "method",
    "middle",   "midnight", "milk",     "million",  "mimic",    "mind",
    "minimum",  "minor",    "minute",   "miracle",  "mirror",   "misery",
    "miss",     "mistake",  "mix",      "mixed",    "mixture",  "mobile",
    "model",    "modify",   "mom",      "moment",   "monitor",  "monkey",
    "monster",  "month",    "moon",     "moral",    "more",     "morning",
    "mosquito", "mother",   "motion",   "motor",    "mountain", "mouse",
    "move",     "movie",    "much",     "muffin",   "mule",     "multiply",
    "muscle",   "museum",   "mushroom", "music",    "must",     "mutual",
    "myself",   "mystery",  "myth",     "naive",    "name",     "napkin",
    "narrow",   "nasty",    "nation",   "nature",   "near",     "neck",
    "need",     "negative", "neglect",  "neither",  "nephew",   "nerve",
    "nest",     "net",      "network",  "neutral",  "never",    "news",
    "next",     "nice",     "night",    "noble",    "noise",    "nominee",
    "noodle",   "normal",   "north",    "nose",     "notable",  "note",
    "nothing",  "notice",   "novel",    "now",      "nuclear",  "number",
    "nurse",    "nut",      "oak",      "obey",     "object",   "oblige",
    "obscure",  "observe",  "obtain",   "obvious",  "occur",    "ocean",
    "october",  "odor",     "off",      "offer",    "office",   "often",
    "oil",      "okay",     "old",      "olive",    "olympic",  "omit",
    "once",     "one",      "onion",    "online",   "only",     "open",
    "opera",    "opinion",  "oppose",   "option",   "orange",   "orbit",
    "orchard",  "order",    "ordinary", "organ",    "orient",   "original",
    "orphan",   "ostrich",  "other",    "outdoor",  "outer",    "output",
    "outside",  "oval",     "oven",     "over",     "own",      "owner",
    "oxygen",   "oyster",   "ozone",    "pact",     "paddle",   "page",
    "pair",     "palace",   "palm",     "panda",    "panel",    "panic",
    "panther",  "paper",    "parade",   "parent",   "park",     "parrot",
    "party",    "pass",     "patch",    "path",     "patient",  "patrol",
    "pattern",  "pause",    "pave",     "payment",  "peace",    "peanut",
    "pear",     "peasant",  "pelican",  "pen",      "penalty",  "pencil",
    "people",   "pepper",   "perfect",  "permit",   "person",   "pet",
    "phone",    "photo",    "phrase",   "physical", "piano",    "picnic",
    "picture",  "piece",    "pig",      "pigeon",   "pill",     "pilot",
    "pink",     "pioneer",  "pipe",     "pistol",   "pitch",    "pizza",
    "place",    "planet",   "plastic",  "plate",    "play",     "please",
    "pledge",   "pluck",    "plug",     "plunge",   "poem",     "poet",
    "point",    "polar",    "pole",     "police",   "pond",     "pony",
    "pool",     "popular",  "portion",  "position", "possible", "post",
    "potato",   "pottery",  "poverty",  "powder",   "power",    "practice",
    "praise",   "predict",  "prefer",   "prepare",  "present",  "pretty",
    "prevent",  "price",    "pride",    "primary",  "print",    "priority",
    "prison",   "private",  "prize",    "problem",  "process",  "produce",
    "profit",   "program",  "project",  "promote",  "proof",    "property",
    "prosper",  "protect",  "proud",    "provide",  "public",   "pudding",
    "pull",     "pulp",     "pulse",    "pumpkin",  "punch",    "pupil",
    "puppy",    "purchase", "purity",   "purpose",  "purse",    "push",
    "put",      "puzzle",   "pyramid",  "quality",  "quantum",  "quarter",
    "question", "quick",    "quit",     "quiz",     "quote",    "rabbit",
    "raccoon",  "race",     "rack",     "radar",    "radio",    "rail",
    "rain",     "raise",    "rally",    "ramp",     "ranch",    "random",
    "range",    "rapid",    "rare",     "rate",     "rather",   "raven",
    "raw",      "razor",    "ready",    "real",     "reason",   "rebel",
    "rebuild",  "recall",   "receive",  "recipe",   "record",   "recycle",
    "reduce",   "reflect",  "reform",   "refuse",   "region",   "regret",
    "regular",  "reject",   "relax",    "release",  "relief",   "rely",
    "remain",   "remember", "remind",   "remove",   "render",   "renew",
    "rent",     "reopen",   "repair",   "repeat",   "replace",  "report",
    "require",  "rescue",   "resemble", "resist",   "resource", "response",
    "result",   "retire",   "retreat",  "return",   "reunion",  "reveal",
    "review",   "reward",   "rhythm",   "rib",      "ribbon",   "rice",
    "rich",     "ride",     "ridge",    "rifle",    "right",    "rigid",
    "ring",     "riot",     "ripple",   "risk",     "ritual",   "rival",
    "river",    "road",     "roast",    "robot",    "robust",   "rocket",
    "romance",  "roof",     "rookie",   "room",     "rose",     "rotate",
    "rough",    "round",    "route",    "royal",    "rubber",   "rude",
    "rug",      "rule",     "run",      "runway",   "rural",    "sad",
    "saddle",   "sadness",  "safe",     "sail",     "salad",    "salmon",
    "salon",    "salt",     "salute",   "same",     "sample",   "sand",
    "satisfy",  "satoshi",  "sauce",    "sausage",  "save",     "say",
    "scale",    "scan",     "scare",    "scatter",  "scene",    "scheme",
    "school",   "science",  "scissors", "scorpion", "scout",    "scrap",
    "screen",   "script",   "scrub",    "sea",      "search",   "season",
    "seat",     "second",   "secret",   "section",  "security", "seed",
    "seek",     "segment",  "select",   "sell",     "seminar",  "senior",
    "sense",    "sentence", "series",   "service",  "session",  "settle",
    "setup",    "seven",    "shadow",   "shaft",    "shallow",  "share",
    "shed",     "shell",    "sheriff",  "shield",   "shift",    "shine",
    "ship",     "shiver",   "shock",    "shoe",     "shoot",    "shop",
    "short",    "shoulder", "shove",    "shrimp",   "shrug",    "shuffle",
    "shy",      "sibling",  "sick",     "side",     "siege",    "sight",
    "sign",     "silent",   "silk",     "silly",    "silver",   "similar",
    "simple",   "since",    "sing",     "siren",    "sister",   "situate",
    "six",      "size",     "skate",    "sketch",   "ski",      "skill",
    "skin",     "skirt",    "skull",    "slab",     "slam",     "sleep",
    "slender",  "slice",    "slide",    "slight",   "slim",     "slogan",
    "slot",     "slow",     "slush",    "small",    "smart",    "smile",
    "smoke",    "smooth",   "snack",    "snake",    "snap",     "sniff",
    "snow",     "soap",     "soccer",   "social",   "sock",     "soda",
    "soft",     "solar",    "soldier",  "solid",    "solution", "solve",
    "someone",  "song",     "soon",     "sorry",    "sort",     "soul",
    "sound",    "soup",     "source",   "south",    "space",    "spare",
    "spatial",  "spawn",    "speak",    "special",  "speed",    "spell",
    "spend",    "sphere",   "spice",    "spider",   "spike",    "spin",
    "spirit",   "split",    "spoil",    "sponsor",  "spoon",    "sport",
    "spot",     "spray",    "spread",   "spring",   "spy",      "square",
    "squeeze",  "squirrel", "stable",   "stadium",  "staff",    "stage",
    "stairs",   "stamp",    "stand",    "start",    "state",    "stay",
    "steak",    "steel",    "stem",     "step",     "stereo",   "stick",
    "still",    "sting",    "stock",    "stomach",  "stone",    "stool",
    "story",    "stove",    "strategy", "street",   "strike",   "strong",
    "struggle", "student",  "stuff",    "stumble",  "style",    "subject",
    "submit",   "subway",   "success",  "such",     "sudden",   "suffer",
    "sugar",    "suggest",  "suit",     "summer",   "sun",      "sunny",
    "sunset",   "super",    "supply",   "supreme",  "sure",     "surface",
    "surge",    "surprise", "surround", "survey",   "suspect",  "sustain",
    "swallow",  "swamp",    "swap",     "swarm",    "swear",    "sweet",
    "swift",    "swim",     "swing",    "switch",   "sword",    "symbol",
    "symptom",  "syrup",    "system",   "table",    "tackle",   "tag",
    "tail",     "talent",   "talk",     "tank",     "tape",     "target",
    "task",     "taste",    "tattoo",   "taxi",     "teach",    "team",
    "tell",     "ten",      "tenant",   "tennis",   "tent",     "term",
    "test",     "text",     "thank",    "that",     "theme",    "then",
    "theory",   "there",    "they",     "thing",    "this",     "thought",
    "three",    "thrive",   "throw",    "thumb",    "thunder",  "ticket",
    "tide",     "tiger",    "tilt",     "timber",   "time",     "tiny",
    "tip",      "tired",    "tissue",   "title",    "toast",    "tobacco",
    "today",    "toddler",  "toe",      "together", "toilet",   "token",
    "tomato",   "tomorrow", "tone",     "tongue",   "tonight",  "tool",
    "tooth",    "top",      "topic",    "topple",   "torch",    "tornado",
    "tortoise", "toss",     "total",    "tourist",  "toward",   "tower",
    "town",     "toy",      "track",    "trade",    "traffic",  "tragic",
    "train",    "transfer", "trap",     "trash",    "travel",   "tray",
    "treat",    "tree",     "trend",    "trial",    "tribe",    "trick",
    "trigger",  "trim",     "trip",     "trophy",   "trouble",  "truck",
    "true",     "truly",    "trumpet",  "trust",    "truth",    "try",
    "tube",     "tuition",  "tumble",   "tuna",     "tunnel",   "turkey",
    "turn",     "turtle",   "twelve",   "twenty",   "twice",    "twin",
    "twist",    "two",      "type",     "typical",  "ugly",     "umbrella",
    "unable",   "unaware",  "uncle",    "uncover",  "under",    "undo",
    "unfair",   "unfold",   "unhappy",  "uniform",  "unique",   "unit",
    "universe", "unknown",  "unlock",   "until",    "unusual",  "unveil",
    "update",   "upgrade",  "uphold",   "upon",     "upper",    "upset",
    "urban",    "urge",     "usage",    "use",      "used",     "useful",
    "useless",  "usual",    "utility",  "vacant",   "vacuum",   "vague",
    "valid",    "valley",   "valve",    "van",      "vanish",   "vapor",
    "various",  "vast",     "vault",    "vehicle",  "velvet",   "vendor",
    "venture",  "venue",    "verb",     "verify",   "version",  "very",
    "vessel",   "veteran",  "viable",   "vibrant",  "vicious",  "victory",
    "video",    "view",     "village",  "vintage",  "violin",   "virtual",
    "virus",    "visa",     "visit",    "visual",   "vital",    "vivid",
    "vocal",    "voice",    "void",     "volcano",  "volume",   "vote",
    "voyage",   "wage",     "wagon",    "wait",     "walk",     "wall",
    "walnut",   "want",     "warfare",  "warm",     "warrior",  "wash",
    "wasp",     "waste",    "water",    "wave",     "way",      "wealth",
    "weapon",   "wear",     "weasel",   "weather",  "web",      "wedding",
    "weekend",  "weird",    "welcome",  "west",     "wet",      "whale",
    "what",     "wheat",    "wheel",    "when",     "where",    "whip",
    "whisper",  "wide",     "width",    "wife",     "wild",     "will",
    "win",      "window",   "wine",     "wing",     "wink",     "winner",
    "winter",   "wire",     "wisdom",   "wise",     "wish",     "witness",
    "wolf",     "woman",    "wonder",   "wood",     "wool",     "word",
    "work",     "world",    "worry",    "worth",    "wrap",     "wreck",
    "wrestle",  "wrist",    "write",    "wrong",    "yard",     "year",
    "yellow",   "you",      "young",    "youth",    "zebra",    "zero",
    "zone",     "zoo",      0,
};
static gui_data_t *p_gui_data = NULL;
static gui_algo_data_t  *p_gui_algo_data=NULL;
#define DATA_FILE_INIT "/mnt/emmc/data/wallet_data.sh"  // 存储路径修改为 /mnt/emmc/data
extern void general_lock_start(void);
extern void startup_screen_start(app_index_t app_index);
extern void * data_get_transaction_format(void);
uint8_t walletInput =0;
WalletInfo *infoWallet;

#define GPIO_PIN 0

// 导出 GPIO 引脚
void export_gpio(int pin) {
    FILE *f = fopen("/sys/class/gpio/export", "w");
    if (f == NULL) {
        perror("Unable to open export file");
        exit(1);
    }
    fprintf(f, "%d", pin);
    fclose(f);
}


// 设置 GPIO 引脚的方向
void set_gpio_direction(int pin, const char *direction) {
    char path[50];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        perror("Unable to open direction file");
        exit(1);
    }
    fprintf(f, "%s", direction);
    fclose(f);
}

// 设置 GPIO 引脚的值
void set_gpio_value(int pin, int value) {
    char path[50];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    FILE *f = fopen(path, "w");
    if (f == NULL) {
        perror("Unable to open value file");
        exit(1);
    }
    fprintf(f, "%d", value);
    fclose(f);
}

// 清理 GPIO 引脚
void unexport_gpio(int pin) {
    FILE *f = fopen("/sys/class/gpio/unexport", "w");
    if (f == NULL) {
        perror("Unable to open unexport file");
        exit(1);
    }
    fprintf(f, "%d", pin);
    fclose(f);
}

uint16_t get_rand_num(uint16_t max)
{
	srand(lv_tick_get() + p_gui_data->last_rand);
	p_gui_data->last_rand = rand();
	printf("num : %d\n", p_gui_data->last_rand % max);
	return p_gui_data->last_rand % max;
}


void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' ')) {
        str[len - 1] = '\0';
    }
}

char * gui_algo_data_get_pagelocation(void)
{
    printf("p_gui_algo_data->page_location:%s\r\n",p_gui_algo_data->page_location);
    return p_gui_algo_data->page_location;
}
/**address数据导入**/
uint8_t gui_algo_data_set_address(char *count)  
{
    memcpy(p_gui_algo_data->address_data, count, strlen(count) + 1);  // +1 包括 '\0'
    return 1;
}

uint8_t gui_algo_data_set_addresspath(char *count)  
{
    memcpy(p_gui_algo_data->address_datapath, count, strlen(count) + 1);  // +1 包括 '\0'
    return 1;
}



/****网页定位*****countsaves = 1是保存当前页面，0不进行保存*/
// 设置页面定位
void gui_algo_data_set_pagelocation(char *count, uint8_t countsave) {
    // 检查输入字符串是否为空
    if (count == NULL) {
        printf("Error: count is NULL\n");
        return;
    }
    // 去除换行符或多余空格
    trim_newline(count);
    // 复制 count 到 page_location，包括结尾的 '\0'
    memcpy(p_gui_algo_data->page_location, count, strlen(count) + 1);

    // 如果需要保存到 pagt_location_save
    if (countsave == 1) {
                memcpy(p_gui_algo_data->pagt_location_save, count, strlen(count));
                p_gui_algo_data->pagt_location_save[strlen(count)] = '\0'; // 添加 '\0' 结束符
                printf("p_gui_algo_data->pagt_location_save: %s\n", p_gui_algo_data->pagt_location_save);
        } 
    // 打印 page_location 的值
    printf("p_gui_algo_data->page_location: %s\n", p_gui_algo_data->page_location);
}

char * gui_pagelocationsave_printf()
{
    return p_gui_algo_data->page_location;
}
uint8_t gui_algo_data_get_pagelocationsave(char *state) {
    // 检查 p_gui_algo_data->page_location 是否为 NULL
    if (p_gui_algo_data->page_location == NULL) {
        printf("Error: page_location is NULL\n");
        return -1;
    }

    // 根据 state 的值处理不同的逻辑
    if (0 == strcmp("start", state)) {
        if (0 == strcmp("connect_main", p_gui_algo_data->pagt_location_save))
            connect_main_start();
        else if (0 == strcmp("finger_add", p_gui_algo_data->pagt_location_save))
            finger_add_start();
        else if (0 == strcmp("finger_added", p_gui_algo_data->pagt_location_save))
            finger_added_start();
        else if (0 == strcmp("finger_place", p_gui_algo_data->pagt_location_save))
            finger_place_start();
        else if (0 == strcmp("finger_poweron", p_gui_algo_data->pagt_location_save))
            finger_poweron_start();
        else if (0 == strcmp("finger_remove", p_gui_algo_data->pagt_location_save))
            finger_remove_start();
        else if (0 == strcmp("finger_remove2", p_gui_algo_data->pagt_location_save))
            finger_remove2_start();
        else if (0 == strcmp("finger_start", p_gui_algo_data->pagt_location_save))
            finger_start_start();
        else if (0 == strcmp("general_homescreen", p_gui_algo_data->pagt_location_save))
            general_homescreen_start();
        else if (0 == strcmp("general_lock", p_gui_algo_data->pagt_location_save))
            general_lock_start();
        else if (0 == strcmp("general_main", p_gui_algo_data->pagt_location_save))
            general_main_start();
        else if (0 == strcmp("general_shutdown", p_gui_algo_data->pagt_location_save))
            general_shutdown_start();
        else if (0 == strcmp("guide_main", p_gui_algo_data->pagt_location_save))
            guide_main_start();
        else if (0 == strcmp("guide_recovery", p_gui_algo_data->pagt_location_save))
            guide_recovery_start();
        else if (0 == strcmp("guide_tutorial", p_gui_algo_data->pagt_location_save))
            guide_tutorial_start();
        else if (0 == strcmp("menu_main", p_gui_algo_data->pagt_location_save))
            menu_main_start();
        else if (0 == strcmp("settings_about", p_gui_algo_data->pagt_location_save))
            settings_about_start();
        else if (0 == strcmp("settings_change_pin", p_gui_algo_data->pagt_location_save))
            settings_change_pin_start();
        else if (0 == strcmp("settings_complete", p_gui_algo_data->pagt_location_save))
            settings_complete_start();
        else if (0 == strcmp("settings_erase", p_gui_algo_data->pagt_location_save))
            settings_erase_start();
        else if (0 == strcmp("settings_main", p_gui_algo_data->pagt_location_save))
            settings_main_start();
        else if (0 == strcmp("settings_pin_changed", p_gui_algo_data->pagt_location_save))
            settings_pin_changed_start();
        else if (0 == strcmp("settings_power_off", p_gui_algo_data->pagt_location_save))
            settings_power_off_start();
        else if (0 == strcmp("settings_reset", p_gui_algo_data->pagt_location_save))
            settings_reset_start();
        else if (0 == strcmp("settings_security", p_gui_algo_data->pagt_location_save))
            settings_security_start();
        else if (0 == strcmp("startup_done", p_gui_algo_data->pagt_location_save))
            startup_done_start();
        else if (0 == strcmp("startup_enter_pin", p_gui_algo_data->pagt_location_save))
            startup_enter_pin_start(APP_SETTINGS_ERASE);
        else if (0 == strcmp("startup_import_abort", p_gui_algo_data->pagt_location_save))
            startup_import_abort_start();
        else if (0 == strcmp("startup_import_ready", p_gui_algo_data->pagt_location_save))
            startup_import_ready_start();
        else if (0 == strcmp("startup_import_wallet", p_gui_algo_data->pagt_location_save))
            startup_import_wallet_start();
        else if (0 == strcmp("startup_import_word", p_gui_algo_data->pagt_location_save))
            startup_import_word_start();
        else if (0 == strcmp("startup_incorrect_word", p_gui_algo_data->pagt_location_save))
            startup_incorrect_word_start();
        else if (0 == strcmp("startup_invalid_recovery", p_gui_algo_data->pagt_location_save))
            startup_invalid_recovery_start();
        else if (0 == strcmp("startup_language", p_gui_algo_data->pagt_location_save))
            startup_language_start();
        else if (0 == strcmp("startup_power_on", p_gui_algo_data->pagt_location_save))
            startup_power_on_start();
        else if (0 == strcmp("startup_quick_start", p_gui_algo_data->pagt_location_save))
            startup_quick_start_start();
        else if (0 == strcmp("startup_ready_check", p_gui_algo_data->pagt_location_save))
            startup_ready_check_start();
        else if (0 == strcmp("startup_recovery", p_gui_algo_data->pagt_location_save))
            startup_recovery_start();
        else if (0 == strcmp("startup_screen", p_gui_algo_data->pagt_location_save))
            startup_screen_start(APP_GENERAL);
        else if (0 == strcmp("startup_set_pin", p_gui_algo_data->pagt_location_save))
            startup_set_pin_start();
        else if (0 == strcmp("startup_verification", p_gui_algo_data->pagt_location_save))
            startup_verification_start();
        else if (0 == strcmp("view_addr_main", p_gui_algo_data->pagt_location_save))
            view_addr_main_start();
        else if (0 == strcmp("view_ready_waiting", p_gui_algo_data->pagt_location_save))
            view_ready_waiting_start();
        else if (0 == strcmp("view_transaction_confirm", p_gui_algo_data->pagt_location_save))
            view_transaction_confirm_start();
        else if (0 == strcmp("view_transaction_main", p_gui_algo_data->pagt_location_save))
            view_transaction_main_start();
        else if (0 == strcmp("view_transaction_success", p_gui_algo_data->pagt_location_save))
            view_transaction_success_start();
        else if (0 == strcmp("view_transaction_waiting", p_gui_algo_data->pagt_location_save))
            view_transaction_waiting_start();
    } else if (0 == strcmp("stop", state)) {
        if (0 == strcmp("connect_main", p_gui_algo_data->page_location))
            connect_main_stop();
        else if (0 == strcmp("finger_add", p_gui_algo_data->page_location))
            finger_add_stop();
        else if (0 == strcmp("finger_added", p_gui_algo_data->page_location))
            finger_added_stop();
        else if (0 == strcmp("finger_place", p_gui_algo_data->page_location))
            finger_place_stop();
        else if (0 == strcmp("finger_poweron", p_gui_algo_data->page_location))
            finger_poweron_stop();
        else if (0 == strcmp("finger_remove", p_gui_algo_data->page_location))
            finger_remove_stop();
        else if (0 == strcmp("finger_remove2", p_gui_algo_data->page_location))
            finger_remove2_stop();
        else if (0 == strcmp("finger_start", p_gui_algo_data->page_location))
            finger_start_stop();
        else if (0 == strcmp("general_homescreen", p_gui_algo_data->page_location))
            general_homescreen_stop();
        else if (0 == strcmp("general_lock", p_gui_algo_data->page_location))
            general_lock_stop();
        else if (0 == strcmp("general_main", p_gui_algo_data->page_location))
            general_main_stop();
        else if (0 == strcmp("general_shutdown", p_gui_algo_data->page_location))
            general_shutdown_stop();
        else if (0 == strcmp("guide_main", p_gui_algo_data->page_location))
            guide_main_stop();
        else if (0 == strcmp("guide_recovery", p_gui_algo_data->page_location))
            guide_recovery_stop();
        else if (0 == strcmp("guide_tutorial", p_gui_algo_data->page_location))
            guide_tutorial_stop();
        else if (0 == strcmp("menu_main", p_gui_algo_data->page_location))
            menu_main_stop();
        else if (0 == strcmp("settings_about", p_gui_algo_data->page_location))
            settings_about_stop();
        else if (0 == strcmp("settings_change_pin", p_gui_algo_data->page_location))
            settings_change_pin_stop();
        else if (0 == strcmp("settings_complete", p_gui_algo_data->page_location))
            settings_complete_stop();
        else if (0 == strcmp("settings_erase", p_gui_algo_data->page_location))
            settings_erase_stop();
        else if (0 == strcmp("settings_main", p_gui_algo_data->page_location))
            settings_main_stop();
        else if (0 == strcmp("settings_pin_changed", p_gui_algo_data->page_location))
            settings_pin_changed_stop();
        else if (0 == strcmp("settings_power_off", p_gui_algo_data->page_location))
            settings_power_off_stop();
        else if (0 == strcmp("settings_reset", p_gui_algo_data->page_location))
            settings_reset_stop();
        else if (0 == strcmp("settings_security", p_gui_algo_data->page_location))
            settings_security_stop();
        else if (0 == strcmp("startup_done", p_gui_algo_data->page_location))
            startup_done_stop();
        else if (0 == strcmp("startup_enter_pin", p_gui_algo_data->page_location))
            startup_enter_pin_stop();
        else if (0 == strcmp("startup_import_abort", p_gui_algo_data->page_location))
            startup_import_abort_stop();
        else if (0 == strcmp("startup_import_ready", p_gui_algo_data->page_location))
            startup_import_ready_stop();
        else if (0 == strcmp("startup_import_wallet", p_gui_algo_data->page_location))
            startup_import_wallet_stop();
        else if (0 == strcmp("startup_import_word", p_gui_algo_data->page_location))
            startup_import_word_stop();
        else if (0 == strcmp("startup_incorrect_word", p_gui_algo_data->page_location))
            startup_incorrect_word_stop();
        else if (0 == strcmp("startup_invalid_recovery", p_gui_algo_data->page_location))
            startup_invalid_recovery_stop();
        else if (0 == strcmp("startup_language", p_gui_algo_data->page_location))
            startup_language_stop();
        else if (0 == strcmp("startup_power_on", p_gui_algo_data->page_location))
            startup_power_on_stop();
        else if (0 == strcmp("startup_quick_start", p_gui_algo_data->page_location))
            startup_quick_start_stop();
        else if (0 == strcmp("startup_ready_check", p_gui_algo_data->page_location))
            startup_ready_check_stop();
        else if (0 == strcmp("startup_recovery", p_gui_algo_data->page_location))
            startup_recovery_stop();
        else if (0 == strcmp("startup_screen", p_gui_algo_data->page_location))
            startup_screen_stop();
        else if (0 == strcmp("startup_set_pin", p_gui_algo_data->page_location))
            startup_set_pin_stop();
        else if (0 == strcmp("startup_verification", p_gui_algo_data->page_location))
            startup_verification_stop();
        else if (0 == strcmp("view_addr_main", p_gui_algo_data->page_location))
            view_addr_main_stop();
        else if (0 == strcmp("view_ready_waiting", p_gui_algo_data->page_location))
            view_ready_waiting_stop();
        else if (0 == strcmp("view_transaction_confirm", p_gui_algo_data->page_location))
            view_transaction_confirm_stop();
        else if (0 == strcmp("view_transaction_main", p_gui_algo_data->page_location))
            view_transaction_main_stop();
        else if (0 == strcmp("view_transaction_success", p_gui_algo_data->page_location))
            view_transaction_success_stop();
        else if (0 == strcmp("view_transaction_waiting", p_gui_algo_data->page_location))
            view_transaction_waiting_stop();
    } else {
        printf("Error: Unknown state: %s\n", state);
        return -1;
    }

    return 0;
}


/********
直接获取不存储的信息
*********/
//导入钱包
uint8_t import_wallet_init(void)
{

    for(int i=0;i< p_gui_data->word_num;i++)
    {
        printf("p_gui_data->word: %s\r\n", p_gui_data->word[i]);
    }

    
    printf("p_gui_data->word_num: %d\r\n", p_gui_data->word_num); // 这里 word_num 应该是数字，改为 %d

    // 定义一个字符数组来存储拼接后的字符串
    char num[256] = {0};  // 假设拼接后的字符串不会超过 256 个字符
    concatenateStrings(num, p_gui_data->word, p_gui_data->word_num);
    printf("num:%s\r\n",num);

    // 通过助记词初始化钱包，返回的 wallet_data 是一个新的 WalletInfo 指针
    WalletInfo *wallet_data = init_wallet_by_mnemonic(num, "");
    if (wallet_data == NULL) {
        perror("Failed to initialize wallet by mnemonic");
        free(infoWallet); // 释放之前分配的内存
        return -1;
    }

    // 使用 memcpy 将整个结构体的数据复制到 infoWallet 中
    memcpy(infoWallet, wallet_data, sizeof(WalletInfo));

    // 释放 wallet_data 内存，如果是通过 malloc 分配的
    free(wallet_data);


    return infoWallet->is_valid;
}


/*获取modle名称*/
void *gui_data_get_modle_name(void)
{
	return "LIKKIM";
}

/*获取bluetooth名称*/
void *gui_data_get_bluetooth_name(void)
{
	return "LIKKIM";
}

/*获取system*/
void *gui_data_get_system(void)
{
	return "4.9.2 [87061bb-40fd4d1]";
}

/*获取system*/
void *gui_data_get_bluetooth(void)
{
	return "2.3.0 [f8bbd58-4f605f7]";
}

/*获取bootloader*/
void *gui_data_get_bootloader(void)
{
	return "2.5.2 [612c9ab]";
}

/*获取Address的标题*/
void *gui_data_get_address_title(void)
{
	return "Address";
}

/*获取Address的内容*/
void *gui_data_get_address_info(void)
{
	return p_gui_algo_data->address_data;
}

/*获取Address的path*/
void *gui_data_get_address_path(void)
{
	return p_gui_algo_data->address_datapath;
}

/*获取fee_payer的内容*/
void *gui_data_get_transaction_fee_payer(void)
{
	return "fee_payer_info fee_payer_info fee_payer_info fee_payer_info fee_payer_info";
}

/*获取fomat的内容*/
void *gui_data_get_transaction_format(void)
{
	return  data_get_transaction_format();
}

/*获取hash的内容*/
void *gui_data_get_transaction_hash(void)
{
	return data_get_transaction_format();
}






/********
本地存储的信息
*********/
uint8_t gui_data_get_bg_src_id(void)
{
	return p_gui_data->bg_src_id;
}

void *gui_data_get_bg_src(void)
{
	return p_gui_data->bg_src;
}

void gui_data_set_bg_src_id(uint8_t id)
{
    p_gui_data->bg_src_id = id;

	if(id == 0)
		p_gui_data->bg_src = (void *)&img_bg1;
	else if(id == 1)
		p_gui_data->bg_src = (void *)&img_bg2;
	else if(id == 2)
		p_gui_data->bg_src = (void *)&img_bg3;
	else if(id == 3)
		p_gui_data->bg_src = (void *)&img_bg4;
	else if(id == 4)
		p_gui_data->bg_src = (void *)&img_bg5;
	else if(id == 5)
		p_gui_data->bg_src = (void *)&img_bg6;
	else if(id == 6)
		p_gui_data->bg_src = (void *)&img_bg7;
}

language_type_t gui_data_get_language_type(void)
{
	printf("%s %d\n", __func__, p_gui_data->language_type);
	return p_gui_data->language_type;
}

char *gui_data_get_language(void)
{
	//printf("%s %s\n", __func__, p_gui_data->language);
	return p_gui_data->language;
}

void gui_data_set_language(char *language)
{
	printf("%s %s\n", __func__, language);

	if (0 == strcmp("English", language))
		p_gui_data->language_type = 0;
	else if (0 == strcmp("简体中文", language))
		p_gui_data->language_type = 1;
	else if (0 == strcmp("繁體中文", language))
		p_gui_data->language_type = 2;
	else if (0 == strcmp("Français", language))
		p_gui_data->language_type = 3;
	else if (0 == strcmp("Español", language))
		p_gui_data->language_type = 4;
	else if (0 == strcmp("العربية", language))
		p_gui_data->language_type = 5;
	else if (0 == strcmp("日本語", language))
		p_gui_data->language_type = 6;
	else if (0 == strcmp("Русский", language))
		p_gui_data->language_type = 7;
	else if (0 == strcmp("한국어", language))
		p_gui_data->language_type = 8;
	else if (0 == strcmp("Português", language))
		p_gui_data->language_type = 9;
	else if (0 == strcmp("Português do Brasil", language))
		p_gui_data->language_type = 10;
	else if (0 == strcmp("Italiano", language))
		p_gui_data->language_type = 11;
	else if (0 == strcmp("Deutsch", language))
		p_gui_data->language_type = 12;
	else if (0 == strcmp("हिन्दी", language))
		p_gui_data->language_type = 13;
	else if (0 == strcmp("Монгол", language))
		p_gui_data->language_type = 14;
	else if (0 == strcmp("ไทย", language))
		p_gui_data->language_type = 15;
	else if (0 == strcmp("Українська", language))
		p_gui_data->language_type = 16;
	else if (0 == strcmp("Tiếng Việt", language))
		p_gui_data->language_type = 17;
	else if (0 == strcmp("Bahasa Indonesia", language))
		p_gui_data->language_type = 18;
	else if (0 == strcmp("Tagalog", language))
		p_gui_data->language_type = 19;
	else if (0 == strcmp("বাংলা", language))
		p_gui_data->language_type = 20;
	else
	{
		printf("%s, language is invalid: %s\n", __func__, p_gui_data->language);
		return;
	}

	printf("%s set language type %d\n", __func__, p_gui_data->language_type);

	strcpy(p_gui_data->language, language);
}

char *gui_data_get_pin(void)
{
	printf("%s %s\n", __func__, p_gui_data->pin);
	return p_gui_data->pin;
}

void gui_data_set_pin(char *pin)
{
	printf("%s %s\n", __func__, pin);
	strcpy(p_gui_data->pin, pin);
}

uint8_t gui_data_get_word_num(void)
{
	printf("%s %d\n", __func__, p_gui_data->word_num);
	return p_gui_data->word_num;
}

void gui_data_set_word_num(uint8_t word_num)
{
	printf("%s %d\n", __func__, word_num);
	p_gui_data->word_num = word_num;
}

char *gui_data_get_word(uint8_t word_index)
{
	printf("%s index:%d %s\n", __func__, word_index, p_gui_data->word[word_index]);
	return p_gui_data->word[word_index];
}

void gui_data_set_word(uint8_t word_index, char *word)
{
	printf("%s index:%d %s\n", __func__, word_index, word);
	strcpy(p_gui_data->word[word_index], word);

	// if(word_index == gui_data_get_word_num() - 1)
	// 	p_gui_data->word_set_complete = true;
	// else
	// 	p_gui_data->word_set_complete = false;
}

int gui_data_get_shutdown_time(void)
{
	printf("%s %d\n", __func__, p_gui_data->shutdown_time);
	return p_gui_data->shutdown_time;
}

void gui_data_set_shutdown_time(int shutdown_time)
{
	printf("%s %d\n", __func__, shutdown_time);
	p_gui_data->shutdown_time = shutdown_time;
}

int gui_data_get_lock_time(void)
{
	printf("%s %d\n", __func__, p_gui_data->lock_time);
	return p_gui_data->lock_time;
}

void gui_data_set_lock_time(int lock_time)
{
	printf("%s %d\n", __func__, lock_time);
	p_gui_data->lock_time = lock_time;
}

/*获取指纹数量*/
uint8_t gui_data_get_fingerprint_num(void)
{
	return p_gui_data->fingerprint_num;
}
void gui_data_set_fingerprint_num(uint8_t num)
{
	p_gui_data->fingerprint_num = num;
}

/*获取指纹设置进度*/
uint8_t gui_data_get_fingerprint_process(void)
{
	return p_gui_data->fingerprint_process;
}
void gui_data_set_fingerprint_process(uint8_t process)
{
	p_gui_data->fingerprint_process = process;
}
/*获取指纹移除id*/
uint8_t gui_data_get_fingerprint_remove_id(void)
{
	return p_gui_data->fingerprint_remove_id;
}
void gui_data_set_fingerprint_remove_id(uint8_t remove_id)
{
	p_gui_data->fingerprint_remove_id = remove_id;
}

/*获取电量*/
uint8_t gui_data_get_power_level(void)
{
	return p_gui_data->power_level;
}
void gui_data_set_power_level(uint8_t power_level)
{
	p_gui_data->power_level = power_level;
}

/*获取充电状态*/
uint8_t gui_data_get_power_charge(void)
{
	return p_gui_data->power_charge;
}
void gui_data_set_power_charge(uint8_t power_charge)
{
	p_gui_data->power_charge = power_charge;
}

/*获取蓝牙链接状态*/
uint8_t gui_data_get_ble_connect(void)
{
	return p_gui_data->ble_connect;
}
void gui_data_set_ble_connect(uint8_t conncet)
{
	p_gui_data->ble_connect = conncet;
}

/*获取是否是首次启动设备*/
uint8_t gui_data_get_first_poweron(void)
{
	return p_gui_data->first_poweron;
}
void gui_data_set_first_poweron(uint8_t first_poweron)
{
	p_gui_data->first_poweron = first_poweron;
}

/*获取匹配的单词*/
bool gui_data_get_remind_word(char *str, char **char_tab)
{
	bool match = false;
    int count = 0;
    uint8_t str_length = strlen(str);

    for (int i = 0; wordlist[i] != 0; i++) 
    {
        if(wordlist[i][0] < str[0]) continue;
        if (count >= 4 || wordlist[i][0] > str[0]) break;

        if (strncmp(wordlist[i], str, str_length) == 0) 
        {
            char_tab[count] = wordlist[i];
            count++;
            if(strcmp(wordlist[i], str) == 0)
            {
            	match = true;
            }
        }
    }
    return match;
}

/*重置设备*/
void gui_rest_data(void)
{
    gui_data_sueess(0);
    printf("gui_rest_datagui_rest_datagui_rest_datagui_rest_datagui_rest_data\r\n");
     memset(infoWallet, 0, sizeof(WalletInfo));  // 将 infoWallet 内容清零
    memset(p_gui_data, 0, sizeof(gui_data_t));  // 将 p_gui_data 内容清零
    gui_data_set_bg_src_id(5);
    gui_data_set_language("English");
    gui_data_set_pin("666666");
    gui_data_set_word_num(12);
    gui_data_set_shutdown_time(10);
    gui_data_set_lock_time(10);
    gui_data_set_fingerprint_num(0);
    gui_data_set_first_poweron(1);
    gui_data_set_power_level(100);
    startup_screen_start(APP_GENERAL);

}

/*获取随机单词, */
char *gui_data_get_random_word(char *str)
{
	uint16_t rand = get_rand_num(2040);
	if(strcmp(wordlist[rand], str) == 0)
		return wordlist[rand + 1];
	else
		return wordlist[rand];
}

/*获取密码输入错误次数*/
uint8_t gui_data_get_pin_wrong_times(void)
{
	return p_gui_data->pin_wrong_times;
}
void gui_data_set_pin_wrong_times(uint8_t pin_wrong_times)
{
	p_gui_data->pin_wrong_times = pin_wrong_times;
}
/*获取输入密码错误锁定时间是否结束*/
uint8_t gui_data_get_pin_unlock(void)
{
	/*需要硬件对接*/
	return 1;
}
/*设置输入密码错误锁定时间，单位分钟*/
void gui_data_set_pin_lock_time(uint32_t lock_time)
{
	/*需要硬件对接*/

}

/*触发震动，需要调用震动接口*/
void gui_comm_do_shake(uint8_t count)
{
        // 导出 GPIO 引脚 0
    export_gpio(GPIO_PIN);

    // 设置 GPIO 引脚 0 为输出模式
    set_gpio_direction(GPIO_PIN, "out");

    // 设置 GPIO 引脚 0 为高电平
    set_gpio_value(GPIO_PIN, 1);
    printf("GPIO%d set to HIGH\n", GPIO_PIN);

    // 延时 3 秒
    usleep(30000);

    // 设置 GPIO 引脚 0 为低电平
    set_gpio_value(GPIO_PIN, 0);
    printf("GPIO%d set to LOW\n", GPIO_PIN);

    // 清理 GPIO 引脚 0
    unexport_gpio(GPIO_PIN);
	
}

/*导入钱包标志位赋值*/
void wallet_Input_word(uint8_t count)
{
    walletInput =count;

}

/*输出导入钱包标志位*/
uint8_t wallet_Input_get(void)
{
    return walletInput;

}

/*助记词已经创建成功*/
void gui_data_sueess(uint8_t count){
    if(count ==1)
    {

         p_gui_data->word_set_complete =true;
         printf("p_gui_data->word_set_complete = %s\n", p_gui_data->word_set_complete ?"true":"false");

    }
    else if(count ==0)
    {
         p_gui_data->word_set_complete =false;
         printf("p_gui_data->word_set_complete = %s\n", p_gui_data->word_set_complete?"true":"false");

    }
    else
    {
        printf("gui_data_sueess is count fail");
    }
   
    printf("walletinit\r\n");

}

void savedata(void)
{
    SaveWalletToEmmc(p_gui_data);
}

// 保存数据到eMMC
void SaveWalletToEmmc(gui_data_t *data) {
    // 确保目标目录存在
    if (access("/mnt/emmc/data", F_OK) == -1) {
        if (mkdir("/mnt/emmc/data", 0700) == -1) {
            perror("Failed to create directory");
            return;
        }
    }

    FILE *file = fopen(DATA_FILE_INIT, "wb");
    if (!file) {
        perror("Failed to open file for writing SaveWalletToEmmc");
        return;
    }

    // 写入数据
    
    fwrite(&data->last_rand, sizeof(data->last_rand), 1, file);
    fwrite(&data->bg_src_id, sizeof(data->bg_src_id), 1, file);
    fwrite(&data->bg_src, sizeof(data->bg_src), 1, file);
    fwrite(data->pin, sizeof(data->pin), 1, file);
    fwrite(data->language, sizeof(data->language), 1, file);
    fwrite(&data->word_set_complete, sizeof(data->word_set_complete), 1, file);
    fwrite(&data->language_type, sizeof(data->language_type), 1, file);
    fwrite(&data->word_num, sizeof(data->word_num), 1, file);

    for (int i = 0; i < data->word_num; i++) {
        fwrite(data->word[i], sizeof(data->word[i]), 1, file);
    }

    fwrite(&data->lock_time, sizeof(data->lock_time), 1, file);
    fwrite(&data->shutdown_time, sizeof(data->shutdown_time), 1, file);
    fwrite(&data->fingerprint_num, sizeof(data->fingerprint_num), 1, file);
    fwrite(&data->fingerprint_process, sizeof(data->fingerprint_process), 1, file);
    fwrite(&data->fingerprint_remove_id, sizeof(data->fingerprint_remove_id), 1, file);
    fwrite(&data->power_level, sizeof(data->power_level), 1, file);
    fwrite(&data->power_charge, sizeof(data->power_charge), 1, file);
    fwrite(&data->ble_connect, sizeof(data->ble_connect), 1, file);
    fwrite(&data->first_poweron, sizeof(data->first_poweron), 1, file);
    fwrite(&data->pin_wrong_times, sizeof(data->pin_wrong_times), 1, file);

    // 使用 fsync 确保数据写入磁盘
    if (fsync(fileno(file)) == -1) {
        perror("fsync failed");
    }

    fclose(file);
    // printf("Data successfully saved to %s\n", DATA_FILE_INIT);
}

// 读取eMMC中的数据
void ReadWalletForEmmc(gui_data_t *data) {
    FILE *file = fopen(DATA_FILE_INIT, "rb");
    if (!file) {
        data->word_set_complete = false;
        perror("Failed to open file for reading ReadWalletForEmmc");
        return;
    }

    // 读取数据
    
    fread(&data->last_rand, sizeof(data->last_rand), 1, file);
    fread(&data->bg_src_id, sizeof(data->bg_src_id), 1, file);
    fread(&data->bg_src, sizeof(data->bg_src), 1, file);
    fread(data->pin, sizeof(data->pin), 1, file);
    fread(data->language, sizeof(data->language), 1, file);
    fread(&data->word_set_complete, sizeof(data->word_set_complete), 1, file);
    fread(&data->language_type, sizeof(data->language_type), 1, file);
    fread(&data->word_num, sizeof(data->word_num), 1, file);

    for (int i = 0; i < data->word_num; i++) {
        fread(data->word[i], sizeof(data->word[i]), 1, file);
    }

    fread(&data->lock_time, sizeof(data->lock_time), 1, file);
    fread(&data->shutdown_time, sizeof(data->shutdown_time), 1, file);
    fread(&data->fingerprint_num, sizeof(data->fingerprint_num), 1, file);
    fread(&data->fingerprint_process, sizeof(data->fingerprint_process), 1, file);
    fread(&data->fingerprint_remove_id, sizeof(data->fingerprint_remove_id), 1, file);
    fread(&data->power_level, sizeof(data->power_level), 1, file);
    fread(&data->power_charge, sizeof(data->power_charge), 1, file);
    fread(&data->ble_connect, sizeof(data->ble_connect), 1, file);
    fread(&data->first_poweron, sizeof(data->first_poweron), 1, file);
    fread(&data->pin_wrong_times, sizeof(data->pin_wrong_times), 1, file);

    fclose(file);
    // printf("Data successfully read from %s\n", DATA_FILE_INIT);
}


void word_set_completeture(void)
{
    gui_data_set_bg_src_id( p_gui_data->bg_src_id);//锁屏选择
    gui_data_set_language(p_gui_data->language);
    gui_data_set_pin(p_gui_data->pin);
    gui_data_set_word_num(p_gui_data->word_num );//导入助记词的number
    gui_data_set_shutdown_time(p_gui_data->shutdown_time);
    gui_data_set_lock_time(p_gui_data->lock_time);
    gui_data_set_fingerprint_num(p_gui_data->fingerprint_num);
    gui_data_set_first_poweron(p_gui_data->first_poweron);
    gui_data_set_power_level(100);
}
void gui_data_init(void)
{
        // 为 WalletInfo 分配内存并初始化
    infoWallet = (WalletInfo *)malloc(sizeof(WalletInfo));
    if (infoWallet == NULL) {
        perror("Failed to allocate memory for WalletInfo");
        return -1;
    }
    memset(infoWallet, 0, sizeof(WalletInfo)); // 初始化为 0
    
    p_gui_data = (gui_data_t*)lv_mem_alloc(sizeof(gui_data_t));
     p_gui_algo_data = (gui_algo_data_t *)malloc(sizeof(gui_algo_data_t));
    lv_memset(p_gui_data, 0, sizeof(gui_data_t));
    ReadWalletForEmmc(p_gui_data);
    strcpy(p_gui_algo_data->page_location, "startup_screen");
    strcpy(p_gui_algo_data->pagt_location_save, "startup_screen");
    printf("p_gui_data->word_set_complete = %s\n", p_gui_data->word_set_complete ?"true":"false");
    printf("p_gui_data->bg_src_id:%d\r\n",p_gui_data->bg_src_id);

    if(p_gui_data->word_set_complete ==true){
        
        if(import_wallet_init()==1)
         printf("import_wallet_init:succeed\r\n");
    else
        printf("import_wallet_init:fail\r\n");
        startup_screen_start(APP_GENERAL);

    }
    else if (p_gui_data->word_set_complete ==false){
        gui_data_set_bg_src_id(5);
        gui_data_set_language("English");
        gui_data_set_pin("666666");
        gui_data_set_word_num(12);
        gui_data_set_shutdown_time(10);
        gui_data_set_lock_time(10);
        gui_data_set_fingerprint_num(0);
        gui_data_set_first_poweron(1);
        gui_data_set_power_level(100);
        startup_screen_start(APP_GENERAL);
    }
}

void gui_data_deinit(void)
{
    lv_mem_free(p_gui_data);
    p_gui_data = NULL;
}


