import Prelude

-- mTrue: \t f -> t
mTrue :: p1 -> p2 -> p1
mTrue t _ = t

-- mFalse: \t f -> f
mFalse :: p1 -> p2 -> p2
mFalse _ f = f

-- toBool is for pretty printing
toBool :: (Bool -> Bool -> t) -> t
toBool b = b True False 

-- mIf = \b t f -> b t f
mIf :: p -> p
mIf b = b 

-- mAnd = \x y t f -> x (y t f) f
mAnd :: (t1 -> t2 -> t3) -> (t4 -> t2 -> t1) -> t4 -> t2 -> t3
mAnd x y t f = x (y t f) f

-- mOr = \x y t f -> x t (y t f)
mOr :: (t1 -> t2 -> t3) -> (t1 -> t4 -> t2) -> t1 -> t4 -> t3
mOr x y t f = x t (y t f)

-- mNot = \x t f -> x f t
mNot :: (t1 -> t2 -> t3) -> t2 -> t1 -> t3
mNot x t f = x f t